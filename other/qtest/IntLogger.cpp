
#include <assert.h>
#include <unistd.h>

#include "IntLogger.h"

/* constructor
 * */
IntLogDataPool::IntLogDataPool()
{
    // malloc pool
    _ilds_pool = (IntLogData *)malloc(INT_LOG_DATA_POOL_SIZE * sizeof(IntLogData));
    assert(_ilds_pool);

    // init pool
    for(int i = 0; i < INT_LOG_DATA_POOL_SIZE; ++i)
    {
        _ilds_pool[i].time = 0;
        _ilds_pool[i].value = 0;
        _ilds_pool[i].next = NULL;
        if(i < INT_LOG_DATA_POOL_SIZE - 1)
        {
            _ilds_pool[i].next = &_ilds_pool[i + 1];
        }
    }
    _ilds_pool[INT_LOG_DATA_POOL_SIZE - 1].next = NULL;

    // init free queue
    _head = &_ilds_pool[0];
    _tail = &_ilds_pool[INT_LOG_DATA_POOL_SIZE - 1];
}

IntLogDataPool::~IntLogDataPool()
{
    // free memory
    free(_ilds_pool);
}

/* get free int-log-data
 *
 * return IntLogData* for success, NULL for failed
 * */
IntLogData* IntLogDataPool::get_free_ild()
{
    IntLogData *ret = _head;

    // pool is busy
    if(!ret)
    {
        return NULL;
    }

    // pop front
    if(_head->next == NULL)
        _head = _tail = NULL;
    else
        _head = _head->next;

    return ret;
}

/* free ild
 * */
void IntLogDataPool::free_ild(IntLogData *ild)
{
    if (!ild)
        return ;

    // clear data
    ild->time = 0;
    ild->value = 0;
    ild->next = NULL;

    // push back
    if(!_head)
        _head = _tail = ild;
    else
    {
        _tail->next = ild;
        _tail = ild;
    }
}


/* constructor
 * filename: log file
 * window: window time
 *
 * */
IntLogger::IntLogger(std::string &filename, int window)
{
    // window cannot bigger than INT_LOG_MAX_WINDOW
    if(window > INT_LOG_MAX_WINDOW)
        assert(0);

    _ildp = new IntLogDataPool();
    assert(_ildp);

    _fp = fopen(filename.c_str(), "a+");
    assert(_fp);

    _window = window;
    _window_buf = window + 3;

    for(int i = 0; i < _window_buf; ++ i)
    {
        _ildq[i].head = NULL;
        _ildq[i].tail = NULL;
    }

    _curr_cursor = 0;
    _curr_time = 0;
}

IntLogger::~IntLogger()
{
    free(_ildp);
    fclose(_fp);
}

/* record log
 * time: log time
 * value: log value
 * */
void IntLogger::Log(int time, int value)
{
    AutoLocker atl(&_mtx);
    IntLogData *ild = _ildp->get_free_ild();

    // pool is busy
    if(!ild)
        return ;

    // init ild
    ild->time = time;
    ild->value = value;
    ild->next = NULL;
    // add log
    add_log(ild);
}

/* add log
 * ild: int-log-data
 *
 * */
void IntLogger::add_log(IntLogData* ild)
{
    // update currnt time
    _curr_time = _curr_time > ild->time ? _curr_time : ild->time;

    int cursor = ild->time %  _window_buf;

    // push back
    if(_ildq[cursor].head == NULL)
        _ildq[cursor].head = _ildq[cursor].tail = ild;
    else
    {
        _ildq[cursor].tail->next = ild;
        _ildq[cursor].tail = ild;
    }
}

/* process log
 * */
void IntLogger::process_log()
{
    int access_count = 0;
    IntLogData *p, *n;
    while(true)
    {
        access_count = 0;

        // init firt cursor
        // TODO: fix bound issue.
        while(!_ildq[_curr_cursor].head)
        {
            _curr_cursor = (_curr_cursor + 1) % _window_buf;
            ++ access_count;
            if(access_count >= _window_buf)
                break;
        }

        // flush data to file
        while(_ildq[_curr_cursor].head &&
              _ildq[_curr_cursor].head->time + _window <= _curr_time)
        {
            p = _ildq[_curr_cursor].head;
            while(p)
            {
                fprintf(_fp, "%d,%d\n", p->time, p->value);
                n = p->next;
                _ildp->free_ild(p);
                p = n;
            }
             _ildq[_curr_cursor].head =  _ildq[_curr_cursor].tail = NULL;

             // next
            _curr_cursor = (_curr_cursor + 1) % _window_buf;
        }
        fflush(_fp);
        sleep(1);
    }
}

/* start process log in a new thread
 * should use thread to excute this function
 * */
void thread_process_log(IntLogger *intlogger)
{
    intlogger->process_log();
}

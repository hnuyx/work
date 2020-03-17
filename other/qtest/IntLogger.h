
#include <stdio.h>
#include <mutex>
#include <string>

#pragma once

#define INT_LOG_MAX_WINDOW     10000
#define INT_LOG_DATA_POOL_SIZE 1000000

#pragma pack(push, 4)
//
typedef struct _INT_LOG_DATA
{
    int time;
    int value;
    struct _INT_LOG_DATA *next;
} IntLogData;

typedef struct _INT_LOG_DATA_QUEUE
{
    IntLogData *head;
    IntLogData *tail;
} IntLogDataQueue;

#pragma pack(pop)

class AutoLocker
{
public:
    AutoLocker(std::mutex *mtx) : _mtx(mtx)
    {
        _mtx->lock();
    }

    ~AutoLocker()
    {
        _mtx->unlock();
    }

private:
    std::mutex *_mtx;
};

/* int-log-data pool
 * */
class IntLogDataPool
{
public:
    /* constructor
     * */
    IntLogDataPool();
    ~IntLogDataPool();

    /* get free int-log-data
     *
     * return IntLogData* for success, NULL for failed
     * */
    IntLogData* get_free_ild();

    /* free ild
     * */
    void free_ild(IntLogData *ild);

private:
    int _pool_size;
    IntLogData *_ilds_pool;
    IntLogData *_head;
    IntLogData *_tail;

};

// int-logger for c++ test
class IntLogger
{
public:
    /* constructor
     * filename: log file
     * window: window time
     *
     * */
    IntLogger(std::string &filename, int window);
    ~IntLogger();

    /* record log
     * time: log time
     * value: log value
     * */
    void Log(int time, int value);

    /* process log
     * */
    void process_log();

private:
    FILE *_fp;
    int _window;
    int _window_buf;

    // log info
    IntLogDataQueue _ildq[INT_LOG_MAX_WINDOW];
    std::mutex _mtx;
    IntLogDataPool *_ildp;

    // time cursor
    int _curr_time;
    int _curr_cursor;

    /* add log
     * ild: int-log-data
     *
     * */
    void add_log(IntLogData* ild);
};


/* start process log in a new thread
 * */
void thread_process_log(IntLogger *intlogger);

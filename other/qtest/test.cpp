
/* test file
 * */

#include <unistd.h>
#include <thread>
#include <string>

#include "IntLogger.h"

#define  MAKE_DATA_THREADS_SIZE  10

// global counter
int g_counter = 0;

void thread_log(IntLogger *intlogger, int t)
{
    while(true)
    {
        intlogger->Log(time(NULL), ++g_counter + t*10000);
        sleep(1);
    }
}


int main()
{
    std::string filename("a.csv");
    IntLogger intlogger(filename, 10);

    // porcess thread
    std::thread *pt = new std::thread(thread_process_log, &intlogger);

    // make data thraad
    std::thread *mdts[MAKE_DATA_THREADS_SIZE];
    for(int i = 0; i < MAKE_DATA_THREADS_SIZE; ++ i)
    {
        mdts[i] = new std::thread(thread_log, &intlogger, i);
    }

    pt->join();
    delete pt;

    for(int i = 0; i < MAKE_DATA_THREADS_SIZE; ++ i)
    {
        mdts[i]->join();
        delete mdts[i];
    }

    return 0;
}

#ifndef __HTTPPROJECT_THREADPOOL_H__
#define __HTTPPROJECT_THREADPOOL_H__

#include "utils/fd_set_utils.h"


namespace http_project
{


template<typename T>
class threadPool
{
public:
    threadPool(int thread_number);


private:
    static void worker(std::shared_ptr<threadPool<T>*>);
    void run();

private:
    unsigned int m_thread_number;
    std::vector<std::shared_ptr<std::thread>>threads;
    std::queue<std::shared_ptr<T>>my_task_queue;    
};


};


#endif
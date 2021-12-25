#ifndef __HTTPPROJECT_THREADPOOL_CPP__
#define __HTTPPROJECT_THREADPOOL_CPP__

#include "threadpool.h"

namespace http_project
{

template<typename T>
threadPool<T>::threadPool(int thread_number):
m_thread_number(thread_number)
{
    assert(m_thread_number > 0);
    for(int i = 0; i < m_thread_number; ++i)
    {
        std::thread t(worker, std::make_shared<threadPool<T>*>(this));
        threads.emplace_back(std::make_shared<std::thread>(t));
    }
} 

template<typename T>
void threadPool<T>::worker(std::shared_ptr<threadPool<T>*>pool)
{
    pool->run();
}

template<typename T>
void threadPool<T>::run()
{

}


};

#endif
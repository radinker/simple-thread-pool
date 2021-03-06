//!/////////////////////////////////////////////////////////////////////////////
//!  \file       SPThreadPool.cpp
//!  \author     Jose Arboleda
//!  \date       2022
//!  \copyright  MIT License
//!/////////////////////////////////////////////////////////////////////////////

#include "SPThreadPool.hpp"

#include <iostream>
#include <SPConfig.hpp>
#include <SPThreadReport.hpp>


CSPThreadPool::CSPThreadPool(): m_terminate{false}
{
    size_t workers = std::thread::hardware_concurrency();

    if (!workers)
        workers = 1;

    //Spawn all available workers
    while (workers--)
        m_threads.push_back(std::thread(&CSPThreadPool::doWork, this));
}


CSPThreadPool::~CSPThreadPool()
{
    m_terminate = true; //Command all workers to terminate

    //Wait for the workers to complete
    for (auto& thread: m_threads) {
        if (thread.joinable())
            thread.join();
    }

#ifdef SP_USE_THREAD_REPORT
    m_threadReport.printThreadReport();
#endif
}

//TODO: replace spin lock with conditional variable
void CSPThreadPool::doWork()
{
    while (!m_terminate) {
        CSPJob job;

        if (popJob(job))
            job.work();
        else
            std::this_thread::yield();
    }
}


bool CSPThreadPool::popJob(CSPJob& job)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    bool emptyQueue = m_jobs.empty();

    if (!emptyQueue) {
        job = std::move(m_jobs.front());
        m_jobs.pop();

#ifdef SP_USE_THREAD_REPORT
        m_threadReport.reportThreadID(std::this_thread::get_id());
#endif
    }

    return !emptyQueue;
}

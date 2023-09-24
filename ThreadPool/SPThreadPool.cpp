//!/////////////////////////////////////////////////////////////////////////////
//!  \file       SPThreadPool.cpp
//!  \author     Jose Arboleda
//!  \date       2023
//!  \copyright  MIT License
//!/////////////////////////////////////////////////////////////////////////////

#include "SPThreadPool.hpp"

#include <chrono>
#include <cstddef>
#include <iostream>
#include <SPThreadReport.hpp>


CSPThreadPool::CSPThreadPool(): m_terminate{false}
{
#ifdef SP_SHOW_VERSION
    printVersion();
#endif

    size_t workers = std::thread::hardware_concurrency();

    if (!workers)
        workers = 1;
    
    //Spawn all available workers
    while (workers--)
        m_threads.push_back(std::thread(&CSPThreadPool::doWork, this));
}


CSPThreadPool::~CSPThreadPool()
{
    //Command all workers to terminate
    m_terminate = true; 
    size_t workers = m_threads.size();

    m_ready.release(static_cast<std::ptrdiff_t>(workers));
     
    //Wait for the workers to complete
    for (auto& thread: m_threads) {
        if (thread.joinable())
            thread.join();
    }

#ifdef SP_USE_THREAD_REPORT
    m_threadReport.printThreadReport();
#endif
}


void CSPThreadPool::doWork()
{
    while (!m_terminate) {
        CSPJob job;

        m_ready.acquire();

        if (popJob(job))
            job.work();
    }
}


bool CSPThreadPool::popJob(CSPJob& job)
{
    std::unique_lock<std::mutex> lock(m_qMutex);
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


void CSPThreadPool::printVersion()
{
    std::cout << "STP version: " 
              << SP_VERSION_MAJOR << "."
              << SP_VERSION_MINOR << "."
              << SP_VERSION_PATCH << "\n\n";
}

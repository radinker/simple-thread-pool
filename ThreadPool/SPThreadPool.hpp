//!/////////////////////////////////////////////////////////////////////////////
//!  \file       SPThreadPool.hpp
//!  \author     Jose Arboleda
//!  \date       2023
//!  \copyright  MIT License
//!/////////////////////////////////////////////////////////////////////////////

#ifndef SP_THREAD_POOL_H
#define SP_THREAD_POOL_H

#include <atomic>
#include <future>
#include <queue>
#include <semaphore>
#include <thread>
#include <type_traits>
#include <vector>
#include <SPConfig.hpp>
#include <SPJob.hpp>
#include <SPThreadReport.hpp>

//!
//! \class CSPThreadPool
//! \brief A simple thread pool
//!
class CSPThreadPool {
    using counting_semaphore = std::counting_semaphore<SP_SEM_MAX_VALUE>;

    std::mutex                m_qMutex;     /*!< Guards access to the jobs queue */
    counting_semaphore        m_ready{0};   /*!< Signals the workers when a new job is ready */
    std::atomic_bool          m_terminate;  /*!< Signals the workers to terminate */
    std::queue<CSPJob>        m_jobs;       /*!< Jobs to be performed by the pool */
    std::vector<std::thread>  m_threads;    /*!< Available workers */

#ifdef SP_THREAD_REPORT_H
    CSPThreadReport           m_threadReport;  /*!< Optional thread record */
#endif

public:
    CSPThreadPool();
    ~CSPThreadPool();

    //!
    //! \brief  This template is used to queue a job for the thread pool to complete
    //! \tparam Fn Type of the callable entity to be executed by the job
    //! \param  f The actual callable entity
    //! \return A future for the caller to wait on the asynchronous result.
    //!         invoke_result is used to deduce the return type of Fn
    //!
    template<typename Fn>
    std::future<typename std::invoke_result<Fn>::type>
    pushJob(Fn f)
    {
        typedef typename std::invoke_result<Fn>::type ResultType;

        //packaged_task is used to wrap f with an asynchronous result
        std::packaged_task<ResultType()> job(std::move(f));
        std::future<ResultType> result(job.get_future());

        {
            std::unique_lock<std::mutex> lock(m_qMutex);
            m_jobs.push(std::move(job));
        }

        m_ready.release();

        return result;
    }

private:
    //!
    //! \brief This is the actual method executed by the worker threads
    //!
    void doWork();

    //!
    //! \brief  Tries to pop job from the queue. This method blocks if resource is busy
    //! \param  job Reference to where the job is going to be placed
    //! \return true on success
    //!
    bool popJob(CSPJob& job);

    //!
    //! \brief  Prints the current STP version
    //!
    static void printVersion();
};

#endif //SP_THREAD_POOL_H

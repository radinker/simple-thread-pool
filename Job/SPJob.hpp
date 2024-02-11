//!/////////////////////////////////////////////////////////////////////////////
//!  \file       SPJob.hpp
//!  \author     Jose Arboleda
//!  \date       2022
//!  \copyright  MIT License
//!/////////////////////////////////////////////////////////////////////////////

#ifndef SP_JOB_H
#define SP_JOB_H

#include <future>
#include <utility>
#include <SPFunctionCall.hpp>

//!
//! \class CSPJob
//! \brief Generic job abstraction. It performs the actual call using an internal pointer
//!
class CSPJob {

    std::unique_ptr<ISPFunctionCall> m_callPtr; /*!< Pointer to an interface that wraps the actual job to be performed */

public:
    CSPJob() = default;

    CSPJob(CSPJob&& job) noexcept: m_callPtr{std::move(job.m_callPtr)} {}

    //!
    //! \brief  Generic constructor to build a job from a callable entity
    //! \tparam F type of the callable entity that performs the actual job
    //!         This is needed to create a job form a packaged_task when adding it
    //!         to the thread pool
    //!
    template<typename F>
    CSPJob(F&& f): m_callPtr{std::make_unique<CSPFunctionCall<F>>(std::forward<F>(f))} {}

    ~CSPJob() = default;

    CSPJob& operator=(CSPJob&& job) noexcept;

    //!
    //! \brief checks the internal pointer m_callPtr and performs the call
    //!
    void work();
};

#endif //SP_JOB_H

//!/////////////////////////////////////////////////////////////////////////////
//!  \file       SPJob.cpp
//!  \author     Jose Arboleda
//!  \date       2022
//!  \copyright  MIT License
//!/////////////////////////////////////////////////////////////////////////////

#include "SPJob.hpp"

#include <iostream>

void CSPJob::work()
{
    if (m_callPtr)
        m_callPtr->call();
    else
        std::cerr << "Null pointer in job object\n";
}


CSPJob& CSPJob::operator=(CSPJob&& job)
{
    m_callPtr = std::move(job.m_callPtr);
    return *this;
}

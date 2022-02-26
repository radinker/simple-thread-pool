//!/////////////////////////////////////////////////////////////////////////////
//!  \file       SPThreadReport.cpp
//!  \author     Jose Arboleda
//!  \date       2022
//!  \copyright  MIT License
//!/////////////////////////////////////////////////////////////////////////////

#include "SPThreadReport.hpp"

#include <iostream>


void CSPThreadReport::reportThreadID(const std::thread::id& id)
{
    m_threads.insert(id);
}


void CSPThreadReport::printThreadReport()
{
    std::cout << "Threads IDs\n"
              << "============================\n";

    for (const auto& thread: m_threads)
        std::cout << "[Thread ID]: " << thread << std::endl;

    std::cout << "============================\n"
              << "Total workers: "
              <<  m_threads.size()
              <<  std::endl;
}

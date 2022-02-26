//!/////////////////////////////////////////////////////////////////////////////
//!  \file       SPThreadReport.hpp
//!  \author     Jose Arboleda
//!  \date       2022
//!  \copyright  MIT License
//!/////////////////////////////////////////////////////////////////////////////

#ifndef SP_THREAD_REPORT_H
#define SP_THREAD_REPORT_H

#include <set>
#include <thread>

//!
//! \class CSPThreadReport
//! \brief Keeps track of the thread IDs and prints them in human readable form
//!
class CSPThreadReport {

    std::set<std::thread::id> m_threads; /*!< A record of all reported workers */

public:
    //!
    //! \brief Records the reporting thread ID
    //! \param id Reporting thread ID
    //!
    void reportThreadID(const std::thread::id& id);

    //!
    //! \brief Prints the thread record to stdout
    //!
    void printThreadReport();
};

#endif //SP_THREAD_REPORT_H

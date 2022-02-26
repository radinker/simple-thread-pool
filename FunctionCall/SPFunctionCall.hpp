//!/////////////////////////////////////////////////////////////////////////////
//!  \file       SPFunctionCall.hpp
//!  \author     Jose Arboleda
//!  \date       2022
//!  \copyright  MIT License
//!/////////////////////////////////////////////////////////////////////////////

#ifndef SP_FUNCTION_CALL_H
#define SP_FUNCTION_CALL_H

#include <utility>

//!
//! \class ISPFunctionCall
//! \brief A simple abstraction to a function call
//!
class ISPFunctionCall {
public:
    virtual void call() = 0;
    virtual ~ISPFunctionCall() {}
};

//!
//! \class  CSPFunctionCall
//! \brief  Generic implementation of ISPFunctionCall
//! \tparam T type of the underlying callable entity
//!
template<typename T>
class CSPFunctionCall: public ISPFunctionCall {

    T fn;  /*!< Callable entity */

public:
    CSPFunctionCall(T&& fn): fn{std::move(fn)} {}

    //!
    //! \brief Wrapper to perform the actual call
    //!
    virtual void call() override
    {
        fn();
    }
};

#endif //SP_FUNCTION_CALL_H

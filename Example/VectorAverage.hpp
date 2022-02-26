//!/////////////////////////////////////////////////////////////////////////////
//!  \file       VectorAverage.hpp
//!  \author     Jose Arboleda
//!  \date       2022
//!  \copyright  MIT License
//!/////////////////////////////////////////////////////////////////////////////

#ifndef VECTOR_AVERAGE_H
#define VECTOR_AVERAGE_H

#include <future>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include <SPThreadPool.hpp>


namespace VectorAverage {
    //!
    //! \brief  Basic function to calculate the average for testing
    //! \param  data Vector containing the values to calculate the average
    //! \return Calculated average
    //!
    template<typename T>
    T Average(const std::vector<T>& data)
    {
        T sum{0};

        if (data.empty())
            return sum;

        for (const auto& value: data)
            sum += value;

        return sum / data.size();
    }

    //!
    //! \brief Calculate the average using available CPUs
    //! \param  data Vector containing the values to calculate the average
    //! \return Calculated average
    //!
    template<typename T>
    T ConcurrentAverage(const std::vector<T>& data)
    {
        T sum{0};
        CSPThreadPool pool;
        std::vector<std::future<T>> results;

        if (data.empty())
            return sum;

        const size_t blockSize = 10;
        auto first = data.begin();
        auto last  = first;

        //Load the thread pool with the input data
        while(first != data.end())
        {
            std::future<T> result;

            if (std::distance(last, data.end()) < blockSize)
                last = data.end();
            else
                std::advance(last, blockSize);

            result = pool.pushJob([=]{
                return std::accumulate(first, last, T{});
            });

            results.push_back(std::move(result));
            first = last;
        }

        //Wait for the results and accumulate
        for (auto& result: results)
           sum += result.get();

        return sum / data.size();
    }
}
#endif //VECTOR_AVERAGE_H

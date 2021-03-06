//!/////////////////////////////////////////////////////////////////////////////
//!  \file       main.cpp
//!  \author     Jose Arboleda
//!  \date       2022
//!  \copyright  MIT License
//!/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>
#include <vector>
#include <VectorAverage.hpp>

int main()
{
    using dataType = uint32_t;
    std::vector<dataType> data {2, 14, 89, 23, 24, 89, 105, 900, 76, 24, 56, 87, 99,
                                3, 23, 44, 21, 90, 45, 768, 405, 90, 33, 47, 92, 16,
                                3, 23, 44, 21, 90, 45, 768, 405, 90, 33, 47, 92, 16,
                                3, 23, 44, 21, 90, 45, 768, 405, 90, 33, 47, 92, 16,
                                3, 23, 44, 21, 90, 45, 768, 405, 90, 33, 47, 92, 16,
                                3, 23, 44, 21, 90, 45, 768, 405, 90, 33, 47, 92, 16,
                                3, 23, 44, 21, 90, 45, 768, 405, 90, 33, 47, 92, 16,
                                3, 23, 44, 21, 90, 45, 768, 405, 90, 33, 47, 92, 16,
                                3, 23, 44, 21, 90, 45, 768, 405, 90, 33, 47, 92, 16,
                                3, 23, 44, 21, 90, 45, 768, 405, 90, 33, 47, 92, 16,
                                3, 23, 44, 21, 90, 45, 768, 405, 90, 33, 47, 92, 16,
                                3, 23, 44, 21, 90, 45, 768, 405, 90, 33, 47, 92, 16,
                                3, 23, 44, 21, 90, 45, 768, 405, 90, 33, 47, 92, 16,
                                1, 19, 79, 67, 88, 12, 223, 800, 54, 32, 21, 25, 18};



    dataType result   = VectorAverage::ConcurrentAverage<dataType>(data);
    dataType expected = VectorAverage::Average<dataType>(data);

    std::cout << "Average : " << result << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << std::endl;

    return 0;
}

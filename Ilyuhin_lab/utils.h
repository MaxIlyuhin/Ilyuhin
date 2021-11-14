#pragma once
#include <iostream>
#include "Pipe.h"
template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((std::cin >> x).fail() || x < min || x > max || std::cin.peek() != '\n')
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Type number (" << min << "-" << max << "):" << " ";
    }
    return x;
}
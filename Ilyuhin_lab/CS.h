#pragma once
#include <string>
#include <iostream>
class CS
{
public:
    int id;
    std::string name;
    int count_of_workshops;
    int working_workshops;
    double efficiency;

    friend std::ostream& operator << (std::ostream& out, const CS& cs);
    friend std::istream& operator >> (std::istream& in, CS& cs);
};


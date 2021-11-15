#pragma once
#include <string>
#include <iostream>
class CS
{
    int idCS;
public:
    static int MaxIDCS;
    std::string name;
    int count_of_workshops;
    int working_workshops;
    double efficiency;

    CS();
    int getIDcs() const;
    friend std::ostream& operator << (std::ostream& out, const CS& cs);
    friend std::istream& operator >> (std::istream& in, CS& cs);
    friend std::ofstream& operator << (std::ofstream& fout, const CS& cs);
    friend std::ifstream& operator >> (std::ifstream& fin, CS& cs);
};


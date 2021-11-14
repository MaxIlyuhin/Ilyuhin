#pragma once
#include <string>
#include <iostream>

class Pipe
{
public:
    int id;
    double length;
    int diameter;
    bool repair;
    std::string name;

    /*void EditPipe();*/
    friend std::ostream& operator << (std::ostream& out, const Pipe& p);
    friend std::istream& operator >> (std::istream& in, Pipe& p);
};


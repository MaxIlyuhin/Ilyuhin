#pragma once
#include <string>
#include <iostream>

class Pipe
{
    int id;
public:
    static int MaxID;
    double length;
    int diameter;
    bool repair;
    std::string name;

    Pipe();
    int getId() const;
    friend std::ostream& operator << (std::ostream& out, const Pipe& p);
    friend std::istream& operator >> (std::istream& in, Pipe& p);
    friend std::ifstream& operator >> (std::ifstream& fin, Pipe& p);
    friend std::ofstream& operator << (std::ofstream& fout, const Pipe& p);
};


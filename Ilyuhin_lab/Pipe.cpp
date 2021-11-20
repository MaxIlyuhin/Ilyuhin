#include "Pipe.h"
#include "utils.h"
#include <fstream>

using namespace std;

int Pipe::MaxID = 0;
Pipe::Pipe()
{
    id = ++MaxID;
}

int Pipe::getId() const
{   
    return id;
}

ostream& operator << (ostream& out, const Pipe& p)
{
    out << "Pipe MaxID" << " " << Pipe::MaxID << endl
        << "Pipe ID" << " " << p.id << endl
        << "Name of the pipe" << " " << p.name << endl
        << "Pipe length is" << " " << p.length << endl
        << "Pipe diameter is" << " " << p.diameter << endl
        << "status:" << " " << ((p.repair == 0) ? "in work" : "in repair") << endl;
    return out;
}

istream& operator >> (istream& in, Pipe& p)
{

    cout << "Please, enter the name of the pipe" << " ";
    cin.clear();
    cin.ignore(10000, '\n');
    getline(cin, p.name);
    cout << "Please, enter the length of the pipe (m)" << " ";
    p.length = GetCorrectNumber(1.0, 500000.0);
    cout << "Please, enter the pipe diameter (mm)" << " ";
    p.diameter = GetCorrectNumber(300, 1420);
    cout << "in repair? (1 - yes; 0 - in work) : ";
    p.repair = GetCorrectNumber(0, 1);
    return in;
}

ifstream& operator >> (ifstream & fin, Pipe & p)
{
    fin >> Pipe::MaxID
        >> p.id
        >> p.name
        >> p.length
        >> p.diameter
        >> p.repair;
    return fin;
}

ofstream& operator << (ofstream& fout, const Pipe& p)
{
   fout << "Pipe" << endl
       << Pipe::MaxID << endl
        << p.id << endl
        << p.name << endl
        << p.length << endl
        << p.diameter << endl
        << p.repair << endl;
    return fout;
}
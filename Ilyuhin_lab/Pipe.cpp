#include "Pipe.h"
#include "utils.h"

using namespace std;

int Pipe::MaxID = 0;
Pipe::Pipe()
{
    id = ++MaxID;
}

//int Pipe::getId() const
//{   
//    return id;
//}

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

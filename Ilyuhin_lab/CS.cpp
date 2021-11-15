#include "CS.h"
#include "utils.h"
#include <fstream>

using namespace std;

int CS::MaxIDCS = 0;
CS::CS()
{
    idCS = ++MaxIDCS;
}

int CS::getIDcs() const
{
    return idCS;
}

ostream& operator << (ostream& out, const CS& cs)
{
    out << "CS MaxID" << " " << CS::MaxIDCS << endl
        << "CS ID" << " " << cs.idCS << endl
        << "Name of CS" << " " << cs.name << endl
        << "Number of workshops" << " " << cs.count_of_workshops << endl
        << "Number of working workshops" << " " << cs.working_workshops << endl
        << "Efficiency" << " " << cs.efficiency << endl;
    return out;
}

istream& operator >> (istream& in, CS& cs)
{
    cout << "Please, enter the name of the station" << " ";
    cin.clear();
    cin.ignore(10000, '\n');
    getline(cin, cs.name);
    cout << "Please, enter the number of shops" << " ";
    cs.count_of_workshops = GetCorrectNumber(0, 10);
    cout << "Please, enter the number of shops in work" << " ";
    cs.working_workshops = GetCorrectNumber(0, cs.count_of_workshops);
    cout << "Please, enter the efficiency" << " ";
    cs.efficiency = GetCorrectNumber(0.0, 1.0);
    return in;
}

ifstream& operator >> (ifstream & fin, CS & cs)
{
    fin >> CS::MaxIDCS
        >> cs.idCS
        >> cs.name
        >> cs.count_of_workshops
        >> cs.working_workshops
        >> cs.efficiency;
    return fin;
}

ofstream& operator << (ofstream& fout, const CS& cs)
{
    fout << "cs" << endl
        << CS::MaxIDCS << endl
        << cs.idCS << endl
        << cs.name << endl
        << cs.count_of_workshops << endl
        << cs.working_workshops << endl
        << cs.efficiency << endl;
    return fout;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Pipe {
    int id;
    double length;
    int diameter;
    bool repair;
    string name;
};

struct CS {
    int id;
    string name;
    int count_of_workshops;
    int working_workshops;
    double efficiency;
};

void PrintMenu()
{
    cout << "-------------------------" << endl
        << "1. Input pipe " << endl
        << "2. Input CS " << endl
        << "3. View all objects " << endl
        << "4. Edit pipe " << endl
        << "5. Edit CS " << endl
        << "6. Save to file " << endl
        << "7. Load from file " << endl
        << "8. Delete Pipe " << endl
        << "9. Delete CS " << endl
        << "10. Search " << endl
        << "0. Exit " << endl
        << "Choose action:" << " ";
}

void ClearStream()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((cin >> x).fail() || x < min || x > max || cin.peek() != '\n')
    {
        ClearStream();
        cout << "Type number (" << min << "-" << max << "):" << " ";
    }
    return x;
}

string InputFileName()
{
    string fname;
    cout << "Input the file name: ";
    ClearStream();
    getline(cin, fname);
    fname = fname + ".txt";
    return fname;
}

void EditPipe(Pipe& p)
{
    cout << "in repair? (1 - yes; 0 - in work) : ";
    if (GetCorrectNumber(0, 1) == 1)
        p.repair = 1;
    else
        p.repair = 0;
}

istream& operator >> (istream& in, Pipe& p)
{
    p.id = 1;
    cout << "Please, enter the name of the pipe" << " ";
    ClearStream();
    getline(cin, p.name);
    cout << "Please, enter the length of the pipe (m)" << " ";
    p.length = GetCorrectNumber(1.0, 500000.0);
    cout << "Please, enter the pipe diameter (mm)" << " ";
    p.diameter = GetCorrectNumber(300, 1420);
    EditPipe(p);
    return in;
}

void EditCS(CS& cs)
{
    cout << "Please, enter the number of shops in work" << " ";
    cs.working_workshops = GetCorrectNumber(1, cs.count_of_workshops);
}

istream& operator >> (istream& in, CS& cs)
{
    cs.id = 2;
    cout << "Please, enter the name of the station" << " ";
    ClearStream();
    getline(cin, cs.name);
    cout << "Please, enter the number of shops" << " ";
    cs.count_of_workshops = GetCorrectNumber(0, 10);
    EditCS(cs);
    cout << "Please, enter the efficiency" << " ";
    cs.efficiency = GetCorrectNumber(0.0, 1.0);
    return in;
}

ostream& operator << (ostream& out, const Pipe& p)
{
    out << "Pipe ID" << " " << p.id << endl
        << "Pipe length is" << " " << p.length << endl
        << "Pipe diameter is" << " " << p.diameter << endl
        << "status:" << " " << ((p.repair == 0) ? "in work" : "in repair") << endl;
    return out;
}

ostream& operator << (ostream& out, const CS& cs)
{
    out << "CS ID" << " " << cs.id << endl
        << "Name of CS" << " " << cs.name << endl
        << "Number of workshops" << " " << cs.count_of_workshops << endl
        << "Number of working workshops" << " " << cs.working_workshops << endl
        << "Efficiency" << " " << cs.efficiency << endl;
    return out;
}

Pipe LoadPipe(ifstream& fin) {
    Pipe p;
    fin >> p.id
        >> p.length
        >> p.diameter
        >> p.repair;
    return p;
}

CS LoadCS(ifstream& fin) {
    CS cs;
    fin >> cs.id
        >> cs.name
        >> cs.count_of_workshops
        >> cs.working_workshops
        >> cs.efficiency;
    return cs;
}

void SavePipe(ofstream& fout, const Pipe& p)
{

    fout << "Pipe" << endl
        << p.id << endl
        << p.length << endl
        << p.diameter << endl
        << p.repair << endl;
}

void SaveCS(ofstream& fout, const CS& cs)
{
    fout << "cs" << endl
        << cs.id << endl
        << cs.name << endl
        << cs.count_of_workshops << endl
        << cs.working_workshops << endl
        << cs.efficiency << endl;
}

Pipe& SelectPipe(vector<Pipe>& p)
{
    cout << "Enter index: ";
    unsigned int index = GetCorrectNumber(1u, p.size()); 
    return p[index - 1];
}

CS& SelectCS(vector <CS>& cs)
{
    cout << "Enter index: ";
    unsigned int index = GetCorrectNumber(1u, cs.size());
    return cs[index - 1];
}

template <typename T>
using Filter1 = bool(*)(const Pipe& p, T param);

bool CheckByPipeName(const Pipe& p, string param)
{
    return p.name == param;
}

bool CheckByLength(const Pipe& p, double param)
{
    return p.length >= param;
}
bool CheckByDiameter(const Pipe& p, int param)
{
    return p.diameter >= param;
}
bool CheckByStatus(const Pipe& p, bool param)
{
    return p.repair == param;
}

template <typename T>
vector <int> FindPipesByFilter(const vector<Pipe>& pipes, Filter1 <T> f, T param)
{
    vector <int> res;
    int i = 0;
    for (auto& p : pipes)
    {
        if (f(p, param))
            res.push_back(i);
        i++;
    }
    if (res.size() == 0)
    {
        cout << "Pipes not found" << endl;
    }
    return res;
}

template <typename T>
using Filter2 = bool(*)(const CS& cs, T param);
bool CheckByName(const CS& cs, string param)
{
    return cs.name == param;
}
bool CheckByPercent(const CS& cs, double param) // разобраться с double
{
    double percent = double(cs.count_of_workshops - cs.working_workshops) / cs.count_of_workshops * 100;
    return percent == param;
}

template <typename T>
vector <int> FindCSesByFilter(const vector<CS>& CSes, Filter2 <T> f, T param)
{
    vector <int> res;
    int i = 0;
    for (auto& cs : CSes)
    {
        if (f(cs, param))
            res.push_back(i);
        i++;
    }
    if (res.size() == 0)
    {
        cout << "CS not found" << endl;
    }
    return res;
}

void DeletePipe(vector<Pipe>& p)
{
    cout << "Enter index : ";
    unsigned int index = GetCorrectNumber(1u, p.size());
    p.erase(p.cbegin() + index - 1);
}

void DeleteCS(vector<CS>& cs)
{
    cout << "Enter index : ";
    unsigned int index = GetCorrectNumber(1u, cs.size());
    cs.erase(cs.cbegin() + index - 1);
}

int main()
{
    vector <Pipe> pipes;
    vector <CS> cses;
    bool pipe_created = false;
    bool cs_created = false;
    while (1)
    {
        PrintMenu();
        switch (GetCorrectNumber(0, 10))
        {
        case 1:
        {
            Pipe p = {};
            cin >> p;
            pipe_created = true;
            pipes.push_back(p);
            break;
        }
        case 2:
        {
            CS cs = {};
            cin >> cs;
            cs_created = true;
            cses.push_back(cs);
            break;
        }
        case 3:
        {
            if (pipe_created)
            {
             for(Pipe p : pipes)
                cout << p;
            }
            if (cs_created)
            {
             for (CS cs : cses)
                cout << cs;
            }
            if (!pipe_created && !cs_created)
                cout << "elements are not created" << endl;
            break;
        }
        case 4:
        {
            if (pipe_created)
            {
                EditPipe(SelectPipe(pipes));
            }
            else
            {
                cout << "Pipe is not created!" << endl;
            }
            break;
        }
        case 5:
        {
            if (cs_created)
            {
                EditCS(SelectCS(cses));
            }
            else
            {
                cout << "CS is not created!" << endl;
            }
            break;
        }
        case 6:
        {
            ofstream fout;
            if (pipe_created && cs_created)
            {
                string FileName = InputFileName();
                fout.open(FileName, ios::out);
                if (fout.is_open())
                {
                    for (Pipe p : pipes)
                    SavePipe(fout, p);
                    for (CS cs : cses)
                    SaveCS(fout, cs);
                    pipe_created = true;
                    cs_created = true;
                }
                else
                {
                    cout << "error writing to file '" << FileName << "'" << endl;
                }
                fout.close();
            }
            else if (pipe_created && !cs_created)
            {

                string FileName = InputFileName();
                fout.open(FileName, ios::out);
                if (fout.is_open())
                {
                    for (Pipe p : pipes)
                    SavePipe(fout, p);
                    pipe_created = true;
                }
                else
                {
                    cout << "error writing to file '" << FileName << "'" << endl;
                }
                fout.close();
            }
            else if (!pipe_created && cs_created)
            {

                string FileName = InputFileName();
                fout.open(FileName, ios::out);
                if (fout.is_open())
                {
                    for (CS cs : cses)
                    SaveCS(fout, cs);
                    cs_created = true;
                }
                else
                {
                    cout << "error writing to file '" << FileName << "'" << endl;
                    cs_created = false;
                    pipe_created = false;
                }
                fout.close();
            }
            else
            {
                cout << "elements are not created" << endl;
            }
            break;
        }
        case 7:
        {
            ifstream fin;
            string FileName = InputFileName();
            fin.open(FileName, ios::in);
            if (fin.is_open())
            {
                string str = {};
                while (!fin.eof())
                {

                    getline(fin, str);
                    if (str == "Pipe")
                    {
                        pipes.push_back(LoadPipe(fin));
                        pipe_created = true;
                    }
                    else if (str == "cs")
                    {
                        cses.push_back(LoadCS(fin));
                        cs_created = true;
                    }
                }
            }
            else
            {
                cout << "error reading from file '" << FileName <<"'" << endl;
            }
            fin.close();
            break;
        }
        case 8:
        {
            if (pipe_created)
            {
                DeletePipe(pipes);
            }
            else
            {
                cout << "Pipe is not created!" << endl;
            }
            break;
        }
        case 9:
        {
            if (cs_created)
            {
                DeleteCS(cses);
            }
            else
            {
                cout << "CS is not created!" << endl;
            }
            break;
        }
        case 10:
        {
            cout << "Find pipes or CS by filter (1 - pipes / 2 - CS) ";
            if (GetCorrectNumber(1, 2) == 1)
            {
                cout << "Find pipes by Filter (1 - name; 2 - length; 3 - diameter; 4 - status) : ";
                switch (GetCorrectNumber(1, 4))
                {
                case 1:
                {
                    string pipename;
                    cout << "Find pipe with name:  ";
                    cin.ignore(10000, '\n');
                    getline(cin, pipename);
                    for (int i : FindPipesByFilter(pipes, CheckByPipeName, pipename))
                        cout << pipes[i];
                    break;
                }
                case 2:
                {
                    cout << "Pipe with a length greater than or equal to (m):  ";
                    double pipelength = GetCorrectNumber(1.0, 500000.0);
                    for (int i : FindPipesByFilter(pipes, CheckByLength, pipelength))
                        cout << pipes[i];
                    break;
                }

                case 3:
                {
                    cout << "Find pipe with diameter (mm):  ";
                    int pipediameter = GetCorrectNumber(300, 1420);
                    for (int i : FindPipesByFilter(pipes, CheckByDiameter, pipediameter))
                        cout << pipes[i];
                    break;
                }

                case 4:
                {
                    cout << "Find pipe with status (1 - in repair; 0 - in work) :  ";
                    bool status = GetCorrectNumber(0, 1);
                    for (int i : FindPipesByFilter(pipes, CheckByStatus, status))
                        cout << pipes[i];
                    break;
                }
                }
            }
            else
            {
                cout << "Find CS (1 - By name / 2 - By percentage of unused workshops) : ";
                if (GetCorrectNumber(1, 2) == 1)
                {
                    string name;
                    cout << "Find CS with name: ";
                    cin.ignore(10000, '\n');
                    getline(cin, name);
                    for (int i : FindCSesByFilter(cses, CheckByName, name))
                        cout << cses[i];
                }
                else
                {
                    cout << "Find CS with percentage of unused workshops : ";
                    double percent = GetCorrectNumber(0.0, 100.0);
                    for (int i : FindCSesByFilter(cses, CheckByPercent, percent))
                        cout << cses[i];
                }
            }
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "wrong action" << endl;
        }
        }
    }
    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Pipe.h"
#include "utils.h"
#include "CS.h"
#include <unordered_map>

using namespace std;

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

void FindPipesMenu()
{
    cout << "--------------------------" << endl
        << "1. Find pipes by name " << endl
        << "2. Find pipes by length " << endl
        << "3. Find pipes by diameter " << endl
        << "4. Find pipes by status " << endl
        << "0. Back to menu " << endl
        << "Choose action: " << " ";
}

void FindCSMenu()
{
    cout << "--------------------------" << endl
        << "1. Find CS by name " << endl
        << "2. Find CS by percentage of unused workshops " << endl
        << "0. Back to menu " << endl
        << "Choose action: " << " ";
}

string InputFileName()
{
    string fname;
    cout << "Input the file name: ";
    cin.clear();
    cin.ignore(10000, '\n');
    getline(cin, fname);
    fname = fname + ".txt";
    return fname;
}

void EditPipe(Pipe& p)
{
    cout << "in repair? (1 - yes; 0 - in work) : ";
    p.repair = GetCorrectNumber(0, 1);
}

void EditCS(CS& cs)
{
    cout << "Please, enter the number of shops in work" << " ";
    cs.working_workshops = GetCorrectNumber(1, cs.count_of_workshops);
}

Pipe& SelectPipe(unordered_map <int, Pipe>& mapPipe)
{
    cout << "Enter index: ";
    unsigned int index = GetCorrectNumber(1u, mapPipe.size());
    return mapPipe[index];
}

CS& SelectCS(unordered_map <int, CS>& mapCS)
{
    cout << "Enter index: ";
    unsigned int index = GetCorrectNumber(1u, mapCS.size());
    return mapCS[index];
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
vector <int> FindPipesByFilter(const unordered_map <int, Pipe>& map, Filter1 <T> f, T param)
{
    vector <int> res;
   
    for (auto& i : map)
    {
        if (f(i.second, param))
            res.push_back(i.first);

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

bool CheckByPercent(const CS& cs, double param)
{
    double percent = double(cs.count_of_workshops - cs.working_workshops) / cs.count_of_workshops * 100;
    return percent == param;
}

template <typename T>
vector <int> FindCSesByFilter(const unordered_map <int, CS>& map, Filter2 <T> f, T param)
{
    vector <int> res;
    for (auto& i : map)
    {
        if (f(i.second, param))
            res.push_back(i.first);
    }
    if (res.size() == 0)
    {
        cout << "CS not found" << endl;
    }
    return res;
}

void packetEditPipe(vector <int>& vect, unordered_map <int, Pipe>& mapPipe)
{
    vector <int> vectEdit;
    cout << "Edit all yes[1]/no[0]: ";
    if (GetCorrectNumber(0, 1))
    {
        vectEdit = vect;
    }
    else
    {
        while (true)
        {
            cout << "enter a number or 0 to complete: ";
            int i = GetCorrectNumber(0, (int)size(vect));
            if (i)
            {
                vectEdit.push_back(vect[i - 1]);
            }
            else
            {
                break;
            }
        }
    }
    cout << "All selected: in repair[1]/ in work[0]/ delete[-1]: ";
    int answer = GetCorrectNumber(-1, 1);
    if (answer == -1)
    {
        for (int id : vectEdit)
        {
            auto search = mapPipe.find(id);
            if (search != mapPipe.end())
                mapPipe.erase(search);
        }
    }
    else
    {
        for (int i : vectEdit)
            mapPipe[i].repair = (bool)answer;
    }
}

template <typename typeElement>
void printVectNumElements(unordered_map <int, typeElement>& map, const vector <int>& vect)
{
    int count = 0;
    for (int i : vect)
    {
        cout << "# " << ++count << endl;
        cout << map[i];
    }
}

void packetEditCS(vector <int>& vect, unordered_map <int, CS>& mapCS)
{
    vector <int> vectEdit = vect;
        cout << "All selected: delete[-1]/ not change[0]: ";
        if (GetCorrectNumber(-1, 0))
        {
            for (int id : vectEdit)
            {
                auto search = mapCS.find(id);
                if (search != mapCS.end())
                    mapCS.erase(search);
            }
        }
}

void Search(unordered_map <int, Pipe>& mapPipe, unordered_map <int, CS>& mapCS)
{
    cout << "What search? Pipe[1]/CS[0]: ";
    if (GetCorrectNumber(0, 1))
    {
        while (true)
        {
            FindPipesMenu();
            vector <int> result;
            switch (GetCorrectNumber(0, 4))
            {
            case 1:
            {
                string pipename;
                cout << "Find pipe with name:  ";
                cin.ignore(10000, '\n');
                getline(cin, pipename);
                result = FindPipesByFilter(mapPipe, CheckByPipeName, pipename);
                break;
            }
            case 2:
            {
                cout << "Pipe with a length greater than or equal to (m):  ";
                double pipelength = GetCorrectNumber(1.0, 500000.0);
                result = FindPipesByFilter(mapPipe, CheckByLength, pipelength);
                break;
            }
            case 3:
            {
                cout << "Find pipe with diameter (mm):  ";
                int pipediameter = GetCorrectNumber(300, 1420);
                result = FindPipesByFilter(mapPipe, CheckByDiameter, pipediameter);
                break;
            }
            case 4:
            {
                cout << "Find pipe with status (1 - in repair; 0 - in work) :  ";
                bool status = GetCorrectNumber(0, 1);
                result = FindPipesByFilter(mapPipe, CheckByStatus, status);
                break;
            }
            case 0:
            {
                return;
            }
            default:
            {
                cout << "Wrong action" << endl;
                break;
            }
            }
            if (size(result))
            {
                printVectNumElements(mapPipe, result);
                packetEditPipe(result, mapPipe);
            }
        }
    }
    else
    {
        while (true)
        {
            FindCSMenu();
            vector <int> result;
            switch (GetCorrectNumber(0, 2))
            {
            case 1:
            {
                string name;
                cout << "Find CS with name: ";
                cin.ignore(10000, '\n');
                getline(cin, name);
                result = FindCSesByFilter(mapCS, CheckByName, name);
                break;
            }
            case 2:
            {
                cout << "Find CS with percentage of unused workshops : ";
                double percent = GetCorrectNumber(0.0, 100.0);
                result = FindCSesByFilter(mapCS, CheckByPercent, percent);
                break;
            }
            case 0:
            {
                return;
            }
            default:
            {
                cout << "Wrong action" << endl;
                break;
            }
            }
            if (size(result))
            {
                printVectNumElements(mapCS, result);
                packetEditCS(result, mapCS);
            }
        }
    }
}

void printMapPipe(const unordered_map <int, Pipe> &mapPipe)
{
    for (auto const& i : mapPipe)
    {
        cout << i.second;
    }
}

void printMapCS(const unordered_map <int, CS>& mapCS)
{
    for (auto const& i : mapCS)
    {
        cout << i.second;
    }
}

void DeletePipe(unordered_map <int, Pipe>& mapPipe)
{
    cout << "Enter index : ";
    unsigned int index = GetCorrectNumber(1u, mapPipe.size());
    mapPipe.erase(index);
}

void DeleteCS(unordered_map <int, CS>& mapCS)
{
    cout << "Enter index : ";
    unsigned int index = GetCorrectNumber(1u, mapCS.size());
    mapCS.erase(index);
}

int main()
{
    bool pipe_created = false;
    bool cs_created = false;
    unordered_map <int, Pipe> mapPipe = {};
    unordered_map <int, CS> mapCS = {};
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
            mapPipe.insert({ p.getId(), p });
            break;
        }
        case 2:
        {
            CS cs = {};
            cin >> cs;
            cs_created = true;
            mapCS.insert({ cs.getIDcs(), cs });
            break;
        }
        case 3:
        {
            if (mapPipe.size())
            {
                cout << "Pipe MaxID" << " " << Pipe::MaxID << endl;
                printMapPipe(mapPipe);
            }
            if (mapCS.size())
            {
                cout << "CS MaxID" << " " << CS::MaxIDCS << endl;
                printMapCS(mapCS);
            }
            if (!pipe_created && !cs_created)
                cout << "elements are not created" << endl;
            break;
        }
        case 4:
        {
            if (pipe_created)
            {
                EditPipe(SelectPipe(mapPipe));
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
                EditCS(SelectCS(mapCS));
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
                    fout << Pipe::MaxID << endl;
                    fout << CS::MaxIDCS << endl;
                    for (auto const& i : mapPipe)
                        fout << i.second;
                    for (auto const& i : mapCS)
                        fout << i.second;
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
                    fout << Pipe::MaxID << endl;
                    for (auto const& i : mapPipe)
                        fout << i.second;
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
                    fout << CS::MaxIDCS << endl;
                    for (auto const& i : mapCS)
                        fout << i.second;
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
            Pipe p;
            CS cs;
            int a = 0, b = 0;
            int line_no = 0;
            string strr = {};
            ifstream fin;
            string FileName = InputFileName();
            fin.open(FileName, ios::in);
            if (fin.is_open())
            {
                mapPipe.clear();
                mapCS.clear();
                string str = {};
                while (!fin.eof())
                {
                    getline(fin, str);
                    if (str == "Pipe")
                    {
                        fin >> p;
                        mapPipe.insert({ p.getId(), p });
                        pipe_created = true;
                        a++;
                    }
                    else if (str == "cs")
                    {
                        fin >> cs;
                        mapCS.insert({ cs.getIDcs(), cs });
                        cs_created = true;
                        b++;
                    }
                }
            }
            else
            {
                cout << "error reading from file '" << FileName << "'" << endl;
            }
            fin.close();
            fin.open(FileName, ios::in);
                if (a > 0 && b > 0)
                {
                    while (line_no != 2 && getline(fin, strr))
                    {
                        ++line_no;
                        if (line_no == 1)
                        Pipe::MaxID = stoi(strr);
                        if (line_no == 2)
                        CS::MaxIDCS = stoi(strr);
                    }
                }
                if (a > 0 && b == 0)
                {
                    getline(fin, strr);
                    Pipe::MaxID = stoi(strr);
                }
                if (a == 0 && b > 0)
                {
                    getline(fin, strr);
                    CS::MaxIDCS = stoi(strr);
                }

            break;
        }
        case 8:
        {
            if (pipe_created)
            {
                DeletePipe(mapPipe);
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
                DeleteCS(mapCS);
            }
            else
            {
                cout << "CS is not created!" << endl;
            }
            break;
        }

        case 10:
        {
            Search(mapPipe, mapCS);
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
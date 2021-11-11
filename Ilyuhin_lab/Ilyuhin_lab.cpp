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
        << "7. Load to file " << endl
        << "0. Exit " << endl
        << "Choose action:" << " ";
}

template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((cin >> x).fail() || x < min || x > max || cin.peek() != '\n')
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number (" << min << "-" << max << "):" << " ";
    }
    return x;
}

void Edit_repair_pipe(Pipe& p)//!!!!!!!!!!!!!!!!!!!!!!!!
{
    while (true)
    {
        cout << "in repair? [y, n]:" << " ";
        char repair;
        cin >> repair;
        if (cin.peek() == '\n')
        {
            if (tolower(repair) == 'y')
            {
                p.repair = 1;
                break;
            }
            else if (tolower(repair) == 'n')
            {
                p.repair = 0;
                break;
            }
            else
            {
                cout << "Not correct input. Please, try again!" << endl;
            }
        }
        else
        {
            cout << "Too many characters. Please, try again!" << endl;
        }
        cin.clear();
        cin.ignore(10000, '\n');

    }
}

Pipe create_pipe()
{
    Pipe p;
    p.id = 1;
    cout << "Please, enter the length of the pipe (m)" << " ";
    p.length = GetCorrectNumber(1.0, 500000.0);
    cout << "Please, enter the pipe diameter (mm)" << " ";
    p.diameter = GetCorrectNumber(300, 1420);
    Edit_repair_pipe(p);
    return p;
}

void Edit_shop_cs(CS& cs)
{
    cout << "Please, enter the number of shops in work" << " ";
    cs.working_workshops = GetCorrectNumber(1, cs.count_of_workshops);
}

CS create_cs() {
    CS cs;
    cs.id = 2;
    cout << "Please, enter the name of the station" << " ";
    cin.clear();
    cin.ignore(10000, '\n');
    getline(cin, cs.name);
    cout << "Please, enter the number of shops" << " ";
    cs.count_of_workshops = GetCorrectNumber(0, 10);
    Edit_shop_cs(cs);
    cout << "Please, enter the efficiency" << " ";
    cs.efficiency = GetCorrectNumber(0.0, 1.0);
    return cs;
}

void print_pipe(const Pipe& p)
{
    cout << "Pipe ID" << " " << p.id << endl;
    cout << "Pipe length is" << " " << p.length << endl;
    cout << "Pipe diameter is" << " " << p.diameter << endl;
    cout << "status:" << " " << ((p.repair == 0) ? "in work" : "in repair") << endl;
}

void print_CS(const CS& cs)
{
    cout << "CS ID" << " " << cs.id << endl;
    cout << "Name of CS" << " " << cs.name << endl;
    cout << "Number of workshops" << " " << cs.count_of_workshops << endl;
    cout << "Number of working workshops" << " " << cs.working_workshops << endl;
    cout << "Efficiency" << " " << cs.efficiency << endl;
}

Pipe load_pipe(ifstream& fin) {
    Pipe p;
    fin >> p.id
        >> p.length
        >> p.diameter
        >> p.repair;
    return p;
}

CS load_CS(ifstream& fin) {
    CS cs;
    fin >> cs.id
        >> cs.name
        >> cs.count_of_workshops
        >> cs.working_workshops
        >> cs.efficiency;
    return cs;
}

void save_pipe(ofstream& fout, const Pipe& p)
{

    fout << "Pipe" << endl
        << p.id << endl
        << p.length << endl
        << p.diameter << endl
        << p.repair << endl;
}

void save_CS(ofstream& fout, const CS& cs)
{
    fout << "cs" << endl
        << cs.id << endl
        << cs.name << endl
        << cs.count_of_workshops << endl
        << cs.working_workshops << endl
        << cs.efficiency << endl;
}

Pipe& SelectPipe(vector<Pipe> g)
{
    cout << "Enter index: ";
    unsigned int index = GetCorrectNumber(1u, g.size()); 
    return g[index - 1];
}
int main()
{
    vector <Pipe> pipes;
   
    CS cs = {};
    bool pipe_created = false;
    bool cs_created = false;
    while (1)
    {
        PrintMenu();
        switch (GetCorrectNumber(0, 7))
        {
        case 1:
        {
            Pipe p = {};
            p = create_pipe();
            pipe_created = true;
            pipes.push_back(p);
            break;
        }
        case 2:
        {
            cs = create_cs();
            cs_created = true;
            break;
        }
        case 3:
        {
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!+++++++++++++
            if (pipe_created)
            {
             for(Pipe p : pipes)
                print_pipe(p);
            }

            if (cs_created)
                print_CS(cs);
            if (!pipe_created && !cs_created)
                cout << "elements are not created" << endl;
            break;
        }
        case 4:
        {
            if (pipe_created)
            {
                //Edit_repair_pipe(SelectPipe(pipes));
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
                Edit_shop_cs(cs);
            }
            else
            {
                cout << "CS is not created!" << endl;
            }
            break;
        }
        //case 6:
        //{
        //    ofstream fout;
        //    if (pipe_created && cs_created)//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //    {
        //        fout.open("all.txt", ios::out);//!!!!!!!!!!!!!!!!!!!!!!!!
        //        if (fout.is_open())
        //        {
        //            save_pipe(fout, p);
        //            save_CS(fout, cs);
        //            pipe_created = true;
        //            cs_created = true;
        //        }
        //        else
        //        {
        //            cout << "error writing to file 'all.txt'";
        //        }
        //        fout.close();
        //    }
        //    else if (pipe_created && !cs_created)
        //    {

        //        fout.open("all.txt", ios::out);
        //        if (fout.is_open())
        //        {
        //            save_pipe(fout, p);
        //            pipe_created = true;
        //        }
        //        else
        //        {
        //            cout << "error writing to file 'all.txt'";
        //        }
        //        fout.close();
        //    }
        //    else if (!pipe_created && cs_created)
        //    {
        //        fout.open("all.txt", ios::out);
        //        if (fout.is_open())
        //        {
        //            save_CS(fout, cs);
        //            cs_created = true;
        //        }
        //        else
        //        {
        //            cout << "error writing to file 'all.txt'";
        //            cs_created = false;
        //            pipe_created = false;
        //        }
        //        fout.close();
        //    }
        //    else
        //    {
        //        cout << "elements are not created" << endl;
        //    }
        //    break;
        //}
        //case 7:
        //{
        //    ifstream fin;
        //    fin.open("all.txt", ios::in);//!!!!!!!!!!!!!!!!!!!!
        //    if (fin.is_open())
        //    {
        //        string str = {};
        //        while (!fin.eof())
        //        {

        //            getline(fin, str);
        //            if (str == "Pipe")
        //            {
        //                p = load_pipe(fin);
        //                pipe_created = true;
        //               // cin.clear();
        //               // cin.ignore(10000, '\n');
        //            }
        //            else if (str == "cs")
        //            {
        //                cs = load_CS(fin);
        //                cs_created = true;
        //               // cin.clear();
        //                //cin.ignore(10000, '\n');
        //            }
        //        }
        //    }
        //    else
        //    {
        //        cout << "error reading from file 'all.txt'" << endl;
        //    }
        //    fin.close();
        //    break;
        //}
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
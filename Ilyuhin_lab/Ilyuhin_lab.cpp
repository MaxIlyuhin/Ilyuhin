#include <iostream>
#include <fstream>
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
Pipe create_pipe() {
    Pipe p;
    cout << "Please, enter id" << " ";
    cin >> p.id;
    cout << "Please, enter the length of the pipe" << " ";
    cin >> p.length;
    cout << "Please, enter the pipe diameter" << " ";
    cin >> p.diameter;
    cout << "In repair?" << " ";
    cin >> p.repair;
    return p;
}
    CS create_cs() {
    CS cs;
    cout << "Please, enter id" << " ";
    cin >> cs.id;
    cout << "Please, enter the name of the station" << " ";
    cin >> cs.name;
    cout << "Please, enter the number of workshops" << " ";
    cin >> cs.count_of_workshops;
    cout << "Please, enter the number of working workshops" << " ";
    cin >> cs.working_workshops;
    cout << "Please, enter the efficiency" << " ";
    cin >> cs.efficiency;
    return cs;
}
    void PrintMenu()
    {
        cout << "1. Input pipe " << endl
            << "2. Input CS " << endl
            << "3. View all objects " << endl
            << "4. Edit pipe " << endl
            << "5. Edit CS " << endl
            << "6. Save to file " << endl
            << "7. Load to file " << endl
            << "0. Exit " << endl
            << "Select the action:" << " ";
    }
    void print_pipe(const Pipe& p)
    {
        cout << "Pipe ID" << " " << p.id << endl;
        cout << "Pipe length is" << " " << p.length << endl;
        cout << "Pipe diameter is" << " " << p.diameter << endl;
        cout << "In repair?" << " " << p.repair << endl;
    }
    void print_CS(const CS& cs)
    {
        cout << "CS ID" << " " << cs.id << endl;
        cout << "Name of CS" << " " << cs.name << endl;
        cout << "Number of workshops" << " " << cs.count_of_workshops << endl;
        cout << "Number of working workshops" << " " << cs.working_workshops << endl;
        cout << "Efficiency" << " " << cs.efficiency << endl;
    }
 Pipe load_pipe() {
     Pipe p;
     ifstream fin;
     fin.open("pipe.txt", ios::in);
     fin >> p.id;
     fin >> p.length;
     fin >> p.diameter;
     fin >> p.repair;
     fin.close();
     return p;
 }
 CS load_CS() {
     CS cs;
     ifstream fin;
     fin.open("CS.txt", ios::in);
     fin >> cs.id;
     fin >> cs.name;
     fin >> cs.count_of_workshops;
     fin >> cs.working_workshops;
     fin >> cs.efficiency;
     fin.close();
     return cs;
 }
 void save_pipe(const Pipe& p)
 {
     ofstream fout;
     fout.open("pipe.txt", ios::out);
     fout << p.id << endl
         << p.length << endl
         << p.diameter << endl
         << p.repair << endl;
     fout.close();
 }
 void save_CS(const CS& cs)
 {
     ofstream fout;
     fout.open("CS.txt", ios::out);
     fout << cs.id << endl
         << cs.name << endl
         << cs.count_of_workshops << endl
         << cs.working_workshops << endl
         << cs.efficiency << endl;
 }
int main()
{
    Pipe p;
    CS cs;
    while (1)
    {
        PrintMenu();
        int i = 0;
        cin >> i;
        switch (i)
        {
        case 1:
        {
            p = create_pipe();
            break;
        }
        case 2:
        {
            cs = create_cs();
            break;
        }
        case 3:
        {
            print_pipe(p);
            print_CS(cs);
           // print_cs(cs);//только все про трубу и все про КС
            break;
        }
        case 4:
        {
            //EditPipe(p);
            break;
        }
        case 5:
        {
            //EditCS(cs);
            break;
        }
        case 6:
        {
            save_pipe(p);
            save_CS(cs);
            //SaveAll(p,cs);
            break;
        }
        case 7:
        {
           // print_pipe(load_pipe());
            print_pipe(load_pipe());
            print_CS(load_CS());
            // p = LoadPipe();
            // cs = LoadPipe();
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
    //Pipe p = create_pipe();
    //print_length_of_pipe(p);
         
    return 0;
}

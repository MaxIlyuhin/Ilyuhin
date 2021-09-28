// Ilyuhin_lab.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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
    p.id = 0;
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
    cs.id = 0;
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
 void print_all(Pipe& p, CS& cs)
    {
        cout << "Pipe ID" << " " << 10 << endl;
        cout << "Pipe length is" << " " << p.length << endl;
        cout << "Pipe diameter is" << " " << p.diameter << endl;
        cout << "In repair?" << " " << p.repair << endl;
        cout << "CS ID" << " " << 20 << endl;
        cout << "Name of CS" << " " << cs.name << endl;
        cout << "Number of workshops" << " " << cs.count_of_workshops << endl;
        cout << "Number of working workshops" << " " << cs.working_workshops << endl;
        cout << "Efficiency" << " " << cs.efficiency << endl;
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
int main()
{
    Pipe p;
    CS cs;
    //CS cs;
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
            print_all (p, cs); //только все про трубу и все про КС
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
            //SaveAll(p,cs);
            break;
        }
        case 7:
        {
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

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

#include <iostream>
using namespace std;

struct Pipe
{
    string name;
    float lenght;
    int diameter;
    bool condition;
};

struct Compressor_Station
{
    string name;
    int workshop_quantity;
    int working_workshops;
    double efficiency;
};

void menu()
{
    cout << "Menu" << endl
        << "1) Create pipe" << endl
        << "2) Create compressor station" << endl
        << "3) Show objects" << endl
        << "4) Edit pipe" << endl
        << "5) Edit compressor station" << endl
        << "6) Save" << endl
        << "7) Import" << endl
        << "0) Exit" << endl;
};

Pipe pipe_create()
{
    string pipe_name;
    float pipe_lenght;
    int pipe_diameter;
    bool pipe_condition;
    cout << "Enter pipe name:";
    cin >> pipe_name;
    cout << "Enter pipe lenght (m):";
    cin >> pipe_lenght;
    cout << "Enter pipe diameter (mm):";
    cin >> pipe_diameter;
    cout << "Enter pipe condition (1 if on repairing, 0 if working):";
    cin >> pipe_condition;
    return { pipe_name, pipe_lenght, pipe_diameter, pipe_condition };
}

Compressor_Station cs_create()
{
    string cs_name;
    int cs_quantity;
    int cs_working;
    double cs_eff;
    cout << "Enter comperssor station name:";
    cin >> cs_name;
    cout << "Enter compressor station workshops quantity:";
    cin >> cs_quantity;
    cout << "Enter quantity of working workshops:";
    cin >> cs_working;
    while (cs_quantity < cs_working) {
        cout << "Wrong" << endl;
        cout << "Enter quantity of working workshops:";
        cin >> cs_working;
    }
    
        cout << "Enter compressor station efficiency:";
        cin >> cs_eff;
        return{ cs_name, cs_quantity, cs_working, cs_eff };
}

void Show_pipes(Pipe pipe)
{
    string work;
    cout << "Pipes:" << endl;

    if (pipe.condition) { work = "repairing"; }
    else { work = "working"; };


    if (pipe.name.empty()) {
        cout << "No pipes" << endl;
    }
    else {
        cout << pipe.name << " " << pipe.lenght << " " << pipe.diameter << " " << work << endl;
    }
  

    cout << endl;
}

void Show_cs(Compressor_Station cs)
{
    cout << "Compressor Stations:" << endl;
    if (cs.name.empty()) {
        cout << "No compressor station" << endl;
    }
    else {
        cout << cs.name << " " << cs.workshop_quantity << " " << cs.working_workshops << " " << cs.efficiency << endl;
    }
    cout << endl;
}

void pipe_edit(Pipe& pipe) {
    string work;
    pipe.condition = !pipe.condition;
    if (pipe.condition) { work = "repairing"; }
    else { work = "working"; };
    cout << "Pipe condition changed, current pipe condition:" << work << endl;
}

void cs_edit(Compressor_Station& cs) {
    int zapros = 0;
    cout << "Current working workshops:" << cs.working_workshops << endl;
    while (1) {
        cout << "Enable or disable workshop (1 to enable, 2 to disable)" << endl;
        cin >> zapros;
        switch (zapros) {
        case 1:
            if (cs.working_workshops < cs.workshop_quantity) {
                cs.working_workshops++;
            }
            else {
                cout << "Number of working workshops can't exceed total number of workshops" << endl;
            }
            break;
        case 2:
            if (cs.working_workshops != 0) {
                cs.working_workshops--;
            }
            else {
                cout << "Number of working workshops can't be less than zero" << endl;
            }
        }   break;
    }
    cout << "Current working workshops:" << cs.working_workshops << endl;
}

int main()
{
    Pipe all_pipes;
    Compressor_Station all_cs;
    int vvod = 0;
    while (1) {
        menu();
        cout << "Enter commmand number:";
        cin >> vvod;
        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (vvod) {
        case 1:
            all_pipes = pipe_create();
            cout << "Pipe created succesfully!" << endl;
            break;
        case 2:
            all_cs = cs_create();
            cout << "Compressor station created succesfully!" << endl;
            break;
        case 3:
            Show_pipes(all_pipes);
            Show_cs(all_cs);
            break;
        case 4: 
            pipe_edit(all_pipes);
            break;
        case 5:
            cs_edit(all_cs);
            break;
        case 0:
            return 0;
        }
    }
}
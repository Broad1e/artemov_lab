#include <iostream> // потоковый ввод-вывод
#include <fstream> // считывание данных и запись в файл
#include <string> // класс для работы со строками
#include <vector> // класс вектора (для контейнеров последовательности)
#include <filesystem> // управляет сведениями о путях, файла и каталогах


using namespace std;


double True_input(double max, string er_out) //проверка ввода
{
	string x;
	bool fl_double1 = 0;
	bool fl_double2 = 0;
	string s1;
	string s2;

	cin >> x;

	auto pos = x.find("."); //поиск точки
	if (pos != string::npos)
	{
		s1 = x.substr(0, pos);
		s2 = x.substr(pos + 1);
	}

	for (const char& el : s1) {
		if (!isdigit(el)) {
			fl_double1 = 1;
			break;
		}
	}
	for (const char& el : s2) {
		if (!isdigit(el)) {
			fl_double2 = 1;
			break;
		}
	}
	while (cin.fail() || fl_double2 || fl_double1)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << er_out << endl;
		cin >> x;

		auto pos = x.find(".");
		if (pos != string::npos)
		{
			s1 = x.substr(0, pos);
			s2 = x.substr(pos + 1);
		}

		fl_double1 = 0;
		fl_double2 = 0;
		for (const char& el : s1) {
			if (!isdigit(el)) {
				fl_double1 = 1;
				break;
			}
		}
		for (const char& el : s2) {
			if (!isdigit(el)) {
				fl_double2 = 1;
				break;
			}
		}

	}

	return stod(x);

}

int True_input_int(int max, string er_out) // проверка на ввод целочисленного значения
{
	string x;
	bool fl_int;
	fl_int = 0;

	cin >> x;
	for (const char& el : x) {
		if (!isdigit(el)) {
			fl_int = 1;
		}
	}
	while (cin.fail() || fl_int)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << er_out << endl;
		cin >> x;
		fl_int = 0;
		for (const char& el : x) {
			if (!isdigit(el)) {
				fl_int = 1;
			}
		}

	}

	return stoi(x);

}



struct Pipe // структура трубы
{
	int id;
	string name;
	double lenght;
	int diameter;
	bool condition;

};

struct Compressor_Station // структура компрессорной станции
{
	int id;
	string name;
	int workshop_quantity;
	int working_workshops;
	double efficiency;

};

 
void menu() // создание меню (списка действий)
{
	cout << "Command List" << endl
		<< "1) Add pipe" << endl
		<< "2) Add compressor station" << endl
		<< "3) Show all objects" << endl
		<< "4) Edit pipe" << endl
		<< "5) Edit compressor station" << endl
		<< "6) Save in file" << endl
		<< "7) Import from file" << endl
		<< "0) Exit" << endl << endl;
};
 
Pipe createPipe(int pipe_id) //создание трубы
{
	string pipe_name;
	double pipe_lenght;
	int pipe_diameter;
	bool pipe_condition;
	string error_output;

	cout << "Enter pipe name: ";
	getline(cin, pipe_name); // getline позволяет прочитать строку из любого потока ввода
	getline(cin, pipe_name);
	cout << "Enter pipe lenght in meters: ";
	pipe_lenght = True_input(1., "Lenght must be double");
	cout << "Enter pipe diameter in milimeters: ";
	pipe_diameter = True_input_int(1, "Diametr must be integer");
	cout << "Enter 0 if pipe is working or another integer if repairing: ";
	pipe_condition = True_input_int(1, "Repairing status must be integer");


	return { pipe_id, pipe_name, pipe_lenght, pipe_diameter, pipe_condition };
};

Compressor_Station createCS(int cs_id) // создание компрессорной станции
{
	string cs_name;
	int cs_workshops_quantity;
	int cs_working_workshops;
	double cs_efficiency;

	cout << "Enter comressor station name: ";
	getline(cin, cs_name);
	getline(cin, cs_name);
	cout << "Enter number of workshops: ";
	cs_workshops_quantity = True_input_int(1, "Workshops quantity must be integer");
	cout << "Enter number of  working workshops: ";
	cs_working_workshops = True_input_int(1, "Working workshops quantity must be integer");
	while (cs_working_workshops > cs_workshops_quantity) //обработка ошибок (число рабочих кс больше общего числа)
	{
		if (cs_working_workshops > cs_workshops_quantity)
		{
			cout << "nubmer of working worshops must be less then total number of workshops" << endl;
			cout << "Enter number of  working workshops: ";
			cs_working_workshops = True_input(1, "Working workshops quantity must be integer");
		};
	};
	cout << "Enter compressor station efficiency: ";
	cs_efficiency = True_input(1., "Efficiency must be double");


	return { cs_id ,cs_name, cs_workshops_quantity, cs_working_workshops, cs_efficiency };
};


void show_pipes(const vector <Pipe>& all_pipes) // отбразить все трубы
{
	string work;
	cout << "Pipes: " << endl;

	for (const Pipe& pipe : all_pipes) {
		if (pipe.condition) { work = "repairing"; }
		else { work = "working"; };
		cout << pipe.id << " Name: " << pipe.name << " Lenght: " << pipe.lenght << " Diametr: " << pipe.diameter << " Working status: " << work << endl;
	}


	cout << endl;

};

void show_cs(const vector <Compressor_Station>& all_cs) //отобразить все кс
{

	cout << "Compressor stations: " << endl;

	for (const Compressor_Station& cs : all_cs) {
		cout << cs.id << " Name: " << cs.name << " Workshops: " << cs.workshop_quantity << " Working workshops: " << cs.working_workshops << " Efficiency: " << cs.efficiency << endl;
	}

	cout << endl;

};

void edit_pipe(vector <Pipe>& all_pipes) //редактирование трубы
{
	string name_edit;
	int working_status;
	bool searched = false;

	show_pipes(all_pipes);
	cout << "Enter pipe name:";
	getline(cin, name_edit);
	getline(cin, name_edit);
	for (Pipe& pipe : all_pipes) {
		if (pipe.name == name_edit)
		{
			searched = true;
			pipe.condition = !pipe.condition;
			break;
		};
	}
	if (!searched) // ошибка, если имя трубы не найдено в списке
	{
		cout << "Wrong pipe name" << endl;
	}

}

void edit_cs(vector <Compressor_Station>& all_cs) // редактирование кс
{
	string name_edit;
	int cs_working_workshops;
	bool searched = false;

	show_cs(all_cs);
	cout << "Enter pipe name:";
	getline(cin, name_edit);
	getline(cin, name_edit);
	for (Compressor_Station& cs : all_cs) {
		if (cs.name == name_edit)
		{
			searched = true;
			cout << "Enter 0 if you want to repair workshop or another positive integer to add working workshop: ";
			cs_working_workshops = True_input(1, "Command must be integer");
			if (cs.working_workshops + 1 > cs.workshop_quantity && cs_working_workshops)
			{
				cout << "nubmer of working worshops must be less then number of workshops" << endl;

			}
			else if (cs.working_workshops - 1 < 0 && !cs_working_workshops) {
				cs.working_workshops++;
				cout << "Number of working workshops must be >0" << endl << endl;
			}
			else if (cs.working_workshops + 1 <= cs.workshop_quantity && cs_working_workshops) {
				cs.working_workshops++;
				cout << "Compressor station has been edited" << endl << endl;
			}
			else {
				cs.working_workshops--;
				cout << "Compressor station has been edited" << endl << endl;
			}
			break;
		};
	}
	if (!searched)
	{
		cout << "Wrong compressor station name" << endl;
	}

}

void Save(const vector <Pipe>& all_pipes, const vector <Compressor_Station>& all_cs) // сохранение в файл
{
	ofstream out;
	string f_name;
	if (all_pipes.size() > 0 && all_cs.size() > 0) {
		cout << "Enter file name: ";
		cin >> f_name;
		out.open("saved/" + f_name + ".txt");
		if (out.is_open() && all_pipes.size() > 0 && all_cs.size() > 0) {
			for (const Pipe& pipe : all_pipes) {
				out << pipe.id << endl << pipe.name << endl << pipe.lenght << endl << pipe.diameter << endl << pipe.condition << endl;
			}

			out << "999" << endl;

			for (const Compressor_Station& cs : all_cs) {
				out << cs.id << endl << cs.name << endl << cs.workshop_quantity << endl << cs.working_workshops << endl << cs.efficiency << endl;
			}

			out << "888";

		}
		out.close();
		cout << "File has been saved " << endl;
	}
	else {
		cout << "There are now objects, create some objects before saving" << endl;
	};



};

void Upload(vector <Pipe>& all_pipes, vector <Compressor_Station>& all_cs) // импорт из файла
{
	ifstream fin;
	string path = "saved";
	vector <filesystem::path> file_names;
	bool searched = false;
	string searshing_file;
	int load_switch;

	for (const auto& entry : filesystem::directory_iterator(path))
	{
		file_names.push_back(entry.path().filename());
		cout << entry.path().filename() << endl;
	}

	cout << "Enter file name: ";
	cin >> searshing_file;

	for (filesystem::path& fname : file_names) {
		if (fname == searshing_file)
		{
			searched = true;

			fin.open("saved/" + searshing_file);
			if (fin.is_open()) {
				cout << "start importing" << endl;
				fin >> load_switch;
				while (load_switch != 999) {

					Pipe pipe;
					pipe.id = load_switch;
					getline(fin, pipe.name);
					getline(fin, pipe.name);
					fin >> pipe.lenght;
					fin >> pipe.diameter;
					fin >> pipe.condition;
					fin >> load_switch;
					all_pipes.push_back(pipe);
				}

				fin >> load_switch;

				while (load_switch != 888) {

					Compressor_Station cs;
					cs.id = load_switch;
					getline(fin, cs.name);
					getline(fin, cs.name);
					fin >> cs.workshop_quantity;
					fin >> cs.working_workshops;
					fin >> cs.efficiency;
					fin >> load_switch;
					all_cs.push_back(cs);
				}


			}
			else {
				cout << "ERROR" << endl;
			}
			fin.close();
			cout << "File has been imported" << endl;
		};
	}
	if (!searched)
	{
		cout << "Wrong file name" << endl;
	}

}

int main()
{
	vector <Pipe> all_pipes;
	vector <Compressor_Station> all_stations;
	int vvod = 0;
	int pipe_id = 0;
	int cs_id = 0;


	while (1)
	{
		menu();
		cout << "Enter command number: ";
		vvod = True_input(1, "Unexpected command, command number must be integer");


		switch (vvod)
		{
		case 1:
			all_pipes.push_back(createPipe(pipe_id));
			cout << "Pipe was created" << endl << endl;
			pipe_id++;
			break;
		case 2:
			all_stations.push_back(createCS(cs_id));
			cout << "Compressor station was created" << endl << endl;
			cs_id++;

			break;
		case 3:
			show_pipes(all_pipes);
			show_cs(all_stations);
			break;
		case 4:
			edit_pipe(all_pipes);
			break;
		case 5:
			edit_cs(all_stations);
			break;
		case 6:
			Save(all_pipes, all_stations);
			break;

		case 7:

			Upload(all_pipes, all_stations);
			break;

		case 0:
			return 0;
		default:
			cout << "Wrong command, please choose command from this list";
			break;
		}

	}

	return 0;
};
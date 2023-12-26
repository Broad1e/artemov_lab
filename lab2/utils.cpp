#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "utils.h"
#include "Pipeline.h"
#include "CompressionStation.h"
using namespace std;

template <typename T>
T InputValue(T min, T max) {
	T x;
	while (!(cin >> x) || x > max || x < min) {
		cout << "Invalid value. Try again: " << endl;
		cerr << x << std::endl;
		cin.clear();
		cin.ignore(1000, '\n');
	}
	cerr << x << endl;
	return x;
}

bool Confirm()
{
	string wish;
	cout << "1 (yes) / 0 (no)?" << endl;
	while (1)
	{
		if (cin >> wish)
		{
			if (wish == "1") {
				cerr << wish << endl;
				return true;
			}
			else if (wish == "0") {
				cerr << wish << endl;
				return false;
			}
		}
		cout << "Invalid value. Try again:" << endl;
	}
}

string InputString() {
	string x;
	for (;;) {
		getline(cin, x);
		if (!x.empty()) {
			cerr << x << endl;
			return x;
		}
	}
	return x;
}

void FilterPipeByRepapair(const unordered_map<int, Pipeline>& pipelines) {
	cout << "\nEnter repairing value : " << endl;
	bool repairing_value = Confirm();
	for (const auto& pair : pipelines) {
		const Pipeline& pipe = pair.second;
		if (pipe.repairing == repairing_value) {
			cout << "Id of pipe: " << pair.first << endl;
			cout << "pipe name: " << pipe.name << endl;
			cout << "pipe length: " << pipe.length << endl;
			cout << "pipe diameter: " << pipe.diameter << endl;
			cout << "Working?: " << (pipe.repairing ? "Yes" : "No") << endl;
			cout << "--------------------------" << endl;
		}
	}
}

void FilterPipeByName(const unordered_map<int, Pipeline>& pipelines) {
	cout << "Enter name : " << endl;
	string name_value = InputString();
	for (const auto& pair : pipelines) {
		const Pipeline& pipe = pair.second;
		if (pipe.name == name_value) {
			cout << "Id of pipe: " << pair.first << endl;
			cout << "pipe name: " << pipe.name << endl;
			cout << "pipe length: " << pipe.length << endl;
			cout << "pipe diameter: " << pipe.diameter << endl;
			cout << "Working?: " << (pipe.repairing ? "Yes" : "No") << endl;
			cout << "--------------------------" << endl;
		}
	}
}

void filterPipe(const unordered_map<int, Pipeline>& pipelines) {
	cout << "\n1.Filter by name" << "\n" << "2.Filter by repairing value" << endl;
	(InputValue<int>(1, 2) == 1) ? FilterPipeByName(pipelines) : FilterPipeByRepapair(pipelines);
}

void FilterStationByName(const unordered_map<int, CompressionStation> stations) {
	cout << "Enter name : " << endl;
	string name_value = InputString();
	for (const auto& pair : stations) {
		const CompressionStation& station = pair.second;
		if (station.name == name_value) {
			cout << "Id of station: " << pair.first << endl;
			cout << "station name: " << station.name << endl;
			cout << "amount of workshops: " << station.WorkshopAmount << endl;
			cout << "proper amount of workshops: " << station.ProperAmount << endl;
			cout << "efficiency coefficient: " << station.coefficient << endl;
			cout << "--------------------------" << endl;
		}
	}
}

void FilterStationByPercent(const unordered_map<int, CompressionStation> stations) {
	cout << "Enter the percentage of unused workshops: " << endl;
	double percent_value = InputValue<double>(0, 100);
	for (const auto& pair : stations) {
		const CompressionStation& station = pair.second;
		if (((station.WorkshopAmount - station.ProperAmount) * 100.0 / station.WorkshopAmount) == percent_value) {
			cout << "Id of station: " << pair.first << endl;
			cout << "station name: " << station.name << endl;
			cout << "amount of workshops: " << station.WorkshopAmount << endl;
			cout << "proper amount of workshops: " << station.ProperAmount << endl;
			cout << "Efficiency coefficient: " << station.coefficient << endl;
			cout << "--------------------------" << endl;
		}
	}
}

void filterStation(const unordered_map<int, CompressionStation> stations) {
	cout << "\n1.Filter by name" << "\n" << "2.Filter by the percentage of unused workshops" << endl;
	(InputValue<int>(1, 2) == 1) ? FilterStationByName(stations) : FilterStationByPercent(stations);
}
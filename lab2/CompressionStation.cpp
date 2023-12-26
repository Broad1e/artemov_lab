#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "CompressionStation.h"
#include "utils.h"
#include <unordered_set>
using namespace std;
int CompressionStation::NextId = 1;

CompressionStation::CompressionStation() {
	this->id = NextId;
	NextId += 1;
}

unordered_set<int> CompressionStation::ChooseIdbyName(const unordered_map<int, CompressionStation>& stations) {
	cout << "Enter object name: " << endl;
	string name = InputString();
	unordered_set<int> SetOfId;
	for (const auto& pair : stations) {
		if (pair.second.name == name) {
			SetOfId.insert(pair.first);
		}
	}
	return SetOfId;
}

void CompressionStation::AddStation() {
	cout << "Enter staion name: " << endl;
	name = InputString();
	cout << "Enter workshops amount" << endl;
	WorkshopAmount = InputValue<int>(0, 10000);
	cout << "Enter amount of working workshops" << endl;
	ProperAmount = InputValue<int>(0, WorkshopAmount);
	cout << "Enter efficiency coefficient 0-1:" << endl;
	coefficient = InputValue<double>(0, 1);
}

void CompressionStation::ViewingStations(const unordered_map<int, CompressionStation> stations) {
	cout << endl << endl << "INFORMATION ABOUT STATIONS:" << endl;
	for (const auto& pair : stations) {
		const CompressionStation& station = pair.second;
		cout << "Id of station: " << pair.first << endl;
		cout << "station name: " << station.name << endl;
		cout << "amount of workshops: " << station.WorkshopAmount << endl;
		cout << "proper amount of workshops: " << station.ProperAmount << endl;
		cout << "efficiency coefficient: " << station.coefficient << endl;
		cout << "--------------------------" << endl;
	}
}

void CompressionStation::ChangeStation(unordered_map<int, CompressionStation>& stations) {
	unordered_set<int> Ids = ChooseIdbyName(stations);
	for (const auto& i : Ids) {
		cout << "At the moment amount of working workshops: " << stations[i].ProperAmount << " from " << stations[i].WorkshopAmount << endl;
		cout << "Would you like to change the working value of the pipe with id=" << i << "?" << endl;
		if (Confirm()) {
			cout << "Enter proper amount of workshops:" << endl;
			stations[i].ProperAmount = InputValue<int>(0, stations[i].WorkshopAmount);
			cout << "The number of workshops has been changed\n" << endl;
		}
	}
}
void CompressionStation::DeleteStation(unordered_map<int, CompressionStation>& stations) {
	unordered_set<int> Ids = ChooseIdbyName(stations);
	for (auto& i : Ids) {
		cout << "Would you like to delete a station with an id=" << i << "?" << endl;
		if (Confirm()) {
			stations.erase(i);
			cout << "Station with Id=" << i << "is deleted\n" << endl;
		}
	}
}

void CompressionStation::SaveStations(const unordered_map<int, CompressionStation>& stations, string fileName) {
	ofstream file(fileName, ios::app);
	if (!file.is_open()) {
		cout << "The file could not be opened" << endl;
	}
	for (const auto& pair : stations) {
		const CompressionStation& station = pair.second;
		file << "Station:" << endl;
		file << pair.first << endl;
		file << station.name << endl;
		file << station.WorkshopAmount << endl;
		file << station.ProperAmount << endl;
		file << station.coefficient << endl;
	}
	file.close();
	cout << "The data is saved from a file: " << fileName << endl;
}


void CompressionStation::LoadStations(unordered_map<int, CompressionStation>& stations, string fileName) {
	string line;
	int id;
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "The file could not be opened" << endl;
		return;
	}
	while (getline(file, line)) {
		if (line == "Station:") {
			CompressionStation station;
			file >> id;
			getline(file, line);
			getline(file, station.name);
			file >> station.WorkshopAmount >> station.ProperAmount >> station.coefficient;
			stations.insert({ id,station });
		}
	}
	file.close();
	cout << "The data is downloaded from a file: " << fileName << endl;
}
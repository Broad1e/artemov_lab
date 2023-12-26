#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class CompressionStation {
	int id;
	static int NextId;
public:
	inline int getid() const { return id; };
	string name;
	int WorkshopAmount;
	int ProperAmount;
	double coefficient;
	CompressionStation();
	void AddStation();
	static void ViewingStations(const unordered_map<int, CompressionStation> stations);
	static void ChangeStation(unordered_map<int, CompressionStation>& stations);
	static unordered_set <int> ChooseIdbyName(const unordered_map<int, CompressionStation>& stations);
	static void DeleteStation(unordered_map<int, CompressionStation>& stations);
	static void SaveStations(const unordered_map<int, CompressionStation>& stations, string fileName);
	static void LoadStations(unordered_map<int, CompressionStation>& stations, string fileName);
};

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Pipeline {
	int id;
	static int NextId;
public:
	inline int getid() const { return id; };
	string name;
	double length;
	double diameter;
	bool repairing;
	Pipeline();
	void AddPipeLine();
	static void ViewingPipes(const unordered_map<int, Pipeline>& pipelines);
	static void ChangePipe(unordered_map<int, Pipeline>& pipelines);
	static void DeletePipe(unordered_map<int, Pipeline>& pipelines);
	static unordered_set <int> ChooseIdbyName(const unordered_map<int, Pipeline>& pipelines);
	static void SavePipes(const unordered_map<int, Pipeline>& pipelines, string fileName);
	static void LoadPipes(unordered_map<int, Pipeline>& pipelines, string fileName);
};

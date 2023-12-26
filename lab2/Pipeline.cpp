#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Pipeline.h"
#include "utils.h"
#include <unordered_set>
using namespace std;
int Pipeline::NextId = 1;

Pipeline::Pipeline() {
	this->id = NextId;
	NextId += 1;
}
unordered_set<int> Pipeline::ChooseIdbyName(const unordered_map<int, Pipeline>& pipelines) {
	cout << "Enter object name: " << endl;
	string name = InputString();
	unordered_set<int> SetOfId;
	for (const auto& pair : pipelines) {
		if (pair.second.name == name) {
			SetOfId.insert(pair.first);
		}
	}
	return SetOfId;
}
void Pipeline::AddPipeLine()
{
	cout << "Enter pipe name: " << endl;
	name = InputString();
	cout << "Enter length of pipe: " << endl;
	length = InputValue<double>(0, 100000000);
	cout << "Enter diameter of pipe:" << endl;
	diameter = InputValue<double>(0, length);
	cout << "Working?" << endl;
	repairing = Confirm();
}

void Pipeline::ViewingPipes(const unordered_map<int, Pipeline>& pipelines) {
	cout << "INFORMATION ABOUT PIPES:" << endl;
	for (const auto& pair : pipelines) {
		cout << "Id of pipe: " << pair.first << endl;
		cout << "pipe name: " << pair.second.name << endl;
		cout << "pipe length: " << pair.second.length << endl;
		cout << "pipe diameter: " << pair.second.diameter << endl;
		cout << "Working?: " << (pair.second.repairing ? "Yes" : "No") << endl;
		cout << "--------------------------" << endl;
	}
}

void Pipeline::ChangePipe(unordered_map<int, Pipeline>& pipelines) {
	unordered_set<int> Ids = ChooseIdbyName(pipelines);
	for (const auto& i : Ids) {
		cout << (pipelines[i].repairing ? "The pipe is working at the moment" : "The pipe is NOT working at the moment") << endl;
		cout << "Would you like to change the working value of the pipe with id=" << i << "?" << endl;
		if (Confirm()) {
			pipelines[i].repairing = !pipelines[i].repairing;
			cout << "Working value is changed\n" << endl;
		}
	}
}
void Pipeline::DeletePipe(unordered_map<int, Pipeline>& pipelines) {
	unordered_set<int> Ids = ChooseIdbyName(pipelines);
	for (const auto& i : Ids) {
		cout << "Would you like to delete the pipe with id=" << i << "?" << endl;
		if (Confirm()) {
			pipelines.erase(i);
			cout << "Pipe with Id=" << i << "is deleted\n" << endl;
		}
	}
}


void Pipeline::SavePipes(const unordered_map<int, Pipeline>& pipelines, string fileName) {
	ofstream file(fileName);
	if (!file.is_open()) {
		cout << "The file could not be opened" << endl;
	}
	for (const auto& pair : pipelines) {
		const Pipeline& pipe = pair.second;
		file << "Pipeline:" << endl;
		file << pair.first << endl;
		file << pipe.name << endl;
		file << pipe.length << endl;
		file << pipe.diameter << endl;
		file << (pipe.repairing ? "Y" : "N") << endl;
	}
	file.close();
}
void Pipeline::LoadPipes(unordered_map<int, Pipeline>& pipelines, string fileName) {
	string line, isRepairing;
	int id;
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "The file could not be opened" << endl;
		return;
	}
	while (getline(file, line)) {
		if (line == "Pipeline:") {
			Pipeline pipe;
			file >> id;
			getline(file, line);
			getline(file, pipe.name);
			file >> pipe.length >> pipe.diameter >> isRepairing;
			pipe.repairing = (isRepairing == "Y" ? true : false);
			pipelines.insert({ id, pipe });
		}
	}
	file.close();
}
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Pipeline.h"
#include "CompressionStation.h"
#include "utils.h"
#include <chrono>
#include <format>

using namespace std;
using namespace chrono;

int main() {
	redirect_output_wrapper cerr_out(cerr);
	ofstream logfile("logging.txt");
	if (logfile)
		cerr_out.redirect(logfile);
	unordered_map<int, Pipeline> pipelines;
	unordered_map<int, CompressionStation> stations;

	for (;;) {
		cout << "Enter 1 to add a pipe\n";
		cout << "Enter 2 to add a station\n";
		cout << "Enter 3 to view the objects\n";
		cout << "Enter 4 to edit pipes\n";
		cout << "Enter 5 to edit stations\n";
		cout << "Enter 6 to save oblects\n";
		cout << "Enter 7 to load objects\n";
		cout << "Enter 0 to EXIT\n";

		switch (InputValue<int>(0, 7)) {
		case 1: {
			Pipeline pipe;
			pipe.AddPipeLine();
			pipelines.insert({ pipe.getid(), pipe });
			cout << "Pipe added." << endl;
			break;
		}
		case 2: {
			CompressionStation station;
			station.AddStation();
			stations.insert({ station.getid(), station });
			cout << "Station added." << endl;
			break;
		}
		case 3: {
			cout << "Would you like to view all items?" << endl;
			if (Confirm()) {
				Pipeline::ViewingPipes(pipelines);
				CompressionStation::ViewingStations(stations);
			}
			else {
				cout << "1.Filter pipes" << "\n" << "2.Filter compessor stations" << endl;
				(InputValue<int>(1, 2) == 1) ? filterPipe(pipelines) : filterStation(stations);
			}
			break;
		}
		case 4: {
			cout << "1. Change repairing value\n" << "2.Delete pipes" << endl;
			(InputValue<int>(1, 2) == 1) ? Pipeline::ChangePipe(pipelines) : Pipeline::DeletePipe(pipelines);
			break;
		}
		case 5: {
			cout << "1.Change the number of working workshops\n" << "2.Delete stations" << endl;
			(InputValue<int>(1, 2) == 1) ? CompressionStation::ChangeStation(stations) : CompressionStation::DeleteStation(stations);
			break;
		}
		case 6: {
			cout << "Enter the file name to save the data: ";
			string fileName = InputString();
			Pipeline::SavePipes(pipelines, fileName);
			CompressionStation::SaveStations(stations, fileName);
			break;
		}
		case 7: {
			cout << "Enter the file name to download the data: ";
			string fileName = InputString();
			Pipeline::LoadPipes(pipelines, fileName);
			CompressionStation::LoadStations(stations, fileName);
			break;
		}
		case 0: {
			return 0;
		}
		default: {
			break;
		}
		}
	}
	return 0;
}
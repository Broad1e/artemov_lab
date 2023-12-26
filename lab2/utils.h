#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Pipeline.h"
#include "CompressionStation.h"
using namespace std;
bool Confirm();
void filterPipe(const unordered_map<int, Pipeline>& pipelines);
void filterStation(const unordered_map<int, CompressionStation> stations);
template <typename T> T InputValue(T min, T max);
string InputString();

class redirect_output_wrapper
{
	ostream& stream;
	streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}

	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};
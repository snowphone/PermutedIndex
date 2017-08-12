#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include "PermutedIndex.h"
typedef std::string str;
#define IN std::ifstream
#define OUT std::ofstream

class IOfile
{
public:
	IOfile(int argc, char* argv[]);
	void getData();
	void getFormattedData();
	~IOfile();

private:
	std::vector<str> fileNames;
	Permuted_Index perIdx;
	string resultFileName(string fileName);
};


inline IOfile::IOfile(int argc, char * argv[])
{

	//���� �Է� �ȵ�.
	if (argc == 1) {
		str fileName;
		cout << "Enter file name" << std::endl;
		cin >> fileName;
		fileNames.push_back(fileName);
	}
	else {
		for (int i = 1; i < argc; ++i) {
			fileNames.push_back(argv[i]);
		}
	}
}

IOfile::~IOfile()
{
}

inline void IOfile::getData()
{
	for (auto& fileName : fileNames) {
		IN in(fileName);
		OUT out(resultFileName(fileName));
		perIdx.input(in);
		perIdx.result(out);
	}
}

inline void IOfile::getFormattedData()
{
	for (auto& fileName : fileNames) {
		IN in(fileName);
		OUT out(resultFileName(fileName));
		perIdx.input(in);

	out<< setw(40) << "---original---" << endl;
	perIdx.showOriginal(out);
	out<< setw(40) << "---permuted index---" << endl
		<< perIdx<< endl;
	}
}

inline string IOfile::resultFileName(string fileName)
{
	if (fileName.find(".txt") == string::npos)
		fileName += ".txt";
	string ele = ("\\");
	auto it = find_end(fileName.begin(), fileName.end(), ele.begin(), ele.end());
	if (it != fileName.end())
		fileName = string(it + 1, fileName.end());
	fileName = "result_" + fileName;
	return fileName;
}

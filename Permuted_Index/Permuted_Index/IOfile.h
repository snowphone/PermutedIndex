#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include "PermutedIndex.h"
typedef std::string str;
using is = std::ifstream;
using os = std::ofstream;

class IOfile
{
public:
	IOfile(int argc, char* argv[]);
	void getData();
	void display();
	~IOfile();

private:
	std::vector<str> fileNames;
	Permuted_Index perIdx;
	string resultFileName(string fileName);
};


inline IOfile::IOfile(int argc, char * argv[])
{

	//파일 입력 안됨.
	if (argc == 1) {
		str fileName;
		cout << "Enter file name: ";
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
//display only results
inline void IOfile::getData()
{
	for (auto& fileName : fileNames) {
		is in(fileName);
		os out(resultFileName(fileName));
		perIdx.setData(in);
		perIdx.result(out);
	}
}

inline void IOfile::display()
{
	for (auto& fileName : fileNames) {
		is in(fileName);
		os out(resultFileName(fileName));
		perIdx.setData(in);

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

#include "PermutedIndex.h"
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
	cout.sync_with_stdio(false);
	try {
		if (argc == 1)
			throw "no input";
	}
	catch (const char* c) { cout << c; while (true); }
#if 0
	bool showOnConsole;
	string file;
	if (argc != 1) {
		showOnConsole = false;
		file = argv[1];
		cout << argv[1] << endl;
	}
	else {
		showOnConsole = true;
		cout << "Enter file name: ";
		cin >> file;
	}
#endif
	ifstream fileIn(argv[1]);
	Permuted_Index peridx;
	peridx.input(fileIn);
	peridx.compute();

	string fileOut = argv[1];
	if(fileOut.find(".txt") == string::npos)
		fileOut += ".txt";
	string ele = ("\\");
	auto it = find_end(fileOut.begin(), fileOut.end(), ele.begin(), ele.end());
	if (it != fileOut.end())
		fileOut = string(it + 1, fileOut.end());
	fileOut = "result_" + fileOut;

	ofstream os(fileOut.c_str());
	cout << fileOut << endl;
	os<< setw(40) << "---original---" << endl;
	peridx.showOriginal(os);
	os<< setw(40) << "---permuted index---" << endl
		<< peridx << endl;

	return 0;
}
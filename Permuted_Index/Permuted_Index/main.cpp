#include "PermutedIndex.h"
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
	cout.sync_with_stdio(false);
	string file;
	if (argc != 1)
		file = argv[1];
	else {
		cout << "Enter file name: ";
		cin >> file;
	}

	bool showOnConsole = true;
	string ans;
	cout << "Do you want to see result on console? (yes, no)";
	cin >> ans;
	if (ans == "no")
		showOnConsole = false;
	Permuted_Index peridx;
	ifstream fileIn(file.c_str());
	peridx.input(fileIn);
	peridx.split();
	peridx.rotate();
	peridx.sort();
	peridx.unrotate();
	ofstream os("result.txt");
	if (showOnConsole)
		peridx.display();
	else
		peridx.display(os);

	return 0;
}
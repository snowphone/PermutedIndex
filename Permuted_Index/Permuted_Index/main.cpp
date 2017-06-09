#include "PermutedIndex.h"
#include <fstream>
using namespace std;

int main() {
	cout.sync_with_stdio(false);
	Permuted_Index peridx;
	ifstream fileIn("input.txt");
	peridx.input(fileIn);
	peridx.split();
	peridx.rotate();
	peridx.sort();
	peridx.unrotate();
	peridx.display();

	return 0;
}
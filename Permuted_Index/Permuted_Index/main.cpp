#include "PermutedIndex.h"
#include "IOfile.h"
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
	IOfile iofile(argc, argv);
	iofile.getFormattedData();
}
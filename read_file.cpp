#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
	string filename = "test.txt";

	ifstream ifile(filename.c_str());

	if (!ifile.is_open()) {
		perror("No such file\n");
		return 1;
	}

	int numOfLines = 0;
	string line;
	while (getline(ifile, line)) {
		numOfLines++;
		cout << line << endl;
	}
	cout << "last line: " << line.size() << endl;

	return 0;
}
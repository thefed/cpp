#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
using namespace std;
int main(){
    // Write a file
    string fileName = "test_file.txt";
    cout << fileName << endl;
    ofstream myfile(fileName.c_str());
    if (!myfile.is_open()) {
        cout << "Unable to open file\n";
        return 1;
    }
    myfile << "This is a line.\n";
    int x = 5;
    myfile << x << endl;
    // myfile << "This is another line.\n";
    myfile.close();

    FILE *pFile = fopen(fileName.c_str(), "rb+");
    assert(pFile && "open file error");

    // Get file size
    fseek(pFile, 0, SEEK_END);
    int size = ftell(pFile);

    fclose(pFile);
    printf("file size: %d\n", size);

    // read a file by getline()
    fileName = "json_file.json";
    string line = "";
    ifstream ifile(fileName.c_str());
    if (!ifile.is_open()) {
        printf("No such file '%s'\n", fileName.c_str());
        return 2;
    }
    int numOfLines = 0;
    while (getline(ifile, line)){
        numOfLines++;
        cout << line << ", " << numOfLines << endl;
    }
    cout << line << ", " << numOfLines << endl;
    myfile.close();
    return 0;
}

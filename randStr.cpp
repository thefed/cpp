// 4/2/2017, Yahoo, generate a random string of length <len>, 0~25 -> a~z, 26~30 -> ' '
//
#include<iostream>
#include<string>
#include<sstream>
#include<ctime>
#include<vector>
using namespace std;

string getRandStr(int length) {
    string res(length, 0);
    for (int i = 0; i < length; i++) {
        int num = rand() % 30;
        res[i] = num < 26 ? num + 'a' : ' ';
    }
    return res;
}

bool isUniqueStr(const string &s) {
    vector<char> table(26, 0);
    for (int i = 0; i < s.size(); i++) {
        if (table[s[i] - 'a']) return false;
        table[s[i] - 'a'] = 1;
    }
    return true;
}

void split(const string &s, char delim, vector<string> &strs) {
   stringstream ss(s);
   string str;
   while (getline(ss, str, delim)) {
      if (str.size() > 0) {
        strs.push_back(str);
      } 
   }
}

template <typename T>
void print(const vector<T> &vec) {
    cout << vec.size() << " elements" << endl;
    for (int i = 0; i < vec.size(); i++) {
        cout << "'" << vec[i] << "'" << endl;
    }
    cout << endl;
}

int main() {
    srand(time(NULL));
   int len = 20;
   string str = getRandStr(len); 
   cout << str << endl;

    vector<string> strs;
    split(str, ' ', strs);
    print<string>(strs);

    // remove str elements with duplicate chars
    for (int i = 0; i < strs.size(); i++) {
        if (!isUniqueStr(strs[i])) strs.erase(strs.begin() + i);
    }
    cout << "after removing duplicates: \n";
    print<string>(strs);

    // test erase function
    vector<int> vec = {0,1,2,3,4,5};
    cout << vec.max_size() << ", " << vec.capacity() << endl;
    vec.erase(vec.begin(), vec.begin() + 2);
    print<int>(vec);
    vec.shrink_to_fit();
    cout << vec.capacity() << ", size=" << vec.size() << endl;
    vec.erase(vec.begin(), vec.end());
    print<int>(vec);
}

// t.cpp, for practice use only
// modulus

#include <iostream>
#include <vector>
#include <algorithm>	// is_sorted
#include <cassert>
#include <map>
#include <string>
#include <set>
#include <unordered_set>
#include <climits>
using namespace std;

// print long decimal
#define printld(expr) printf(#expr " = %ld\n", expr)

// print long unsigned
#define printlu(expr) printf(#expr " = %lu\n", expr)

// print unsigned integer
#define printu(expr) printf(#expr " = %u\n", expr)

// print integer in hexadecimal format
#define printh(expr) printf(#expr " = 0x%04x\n", expr)

void print(const vector<int> &v) {
	for (int n: v) printf("%d, ", n);
	// for (string s: v) cout << s << " ";
	printf("\n");
}

int main() {
	vector<int> nums = {3,30,34,5,9};
    string res = largestNumber(nums);
    assert(res == "9534330");

    vector<int> nums2 = {3,30,32,323};
    string res2 = largestNumber(nums2);
    assert(res == "33233230");

    // {321,32} => "32321"
    // {324,32} => "32432"

	// print(res);
    /*
    cout << string::npos << endl;
    printlu((unsigned long)string::npos);
    printld(LONG_MAX);
    printh(LONG_MAX);

    unsigned x = 12;
    printh(x);
    */

	return 0;	
}
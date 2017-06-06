// LC: 38, count and say
// 4/24/2017
/*
1 -> 1
2 -> 11
3 -> 21
4 -> 1211
5 -> 111221
..
n -> ?
*/

#include <iostream>
#include <cassert>
#include <string>
using namespace std;

string build(string s) {
	string res = "";
	const int len = s.size();
	for (int i = 0; i < len;) {
		// take current num, incrememt index and counter
		char num = s[i];
		int cnt = 1;
		i++;
		// check duplicate chars
		while (i < len && s[i] == s[i - 1]) {
			i++;
			cnt++;
		}
		res += to_string(cnt) + num;
	}
	return res;
}

string countAndSay(int n) {
	string res = "1";
	for (int i = 1; i < n; i++) {
		res = build(res);
	}
	return res;
}

int main() {
	assert(countAndSay(1) == "1");
	assert(countAndSay(2) == "11");
	assert(countAndSay(3) == "21");
	assert(countAndSay(4) == "1211");
	assert(countAndSay(5) == "111221");
	return 0;
}
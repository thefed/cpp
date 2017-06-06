// findArmstrong.cpp between 0-999
// e.g. 407 = 4^3 + 7^3
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

bool isArmstrong(int num) {
	int sum = 0;
	int n = num;
	while (num > 0) {
		int x = num % 10;
		sum += x * x * x;
		if (sum > n) return false;
		num /= 10;
	}
	return sum == n;
}

// num: max number component
vector<int> findArmstrong(int num) {
	vector<int> res;
	// brute force
	int max = num * num * num;
	for (int i = 0; i < max; i++) {
		if (isArmstrong(i)) res.push_back(i);
	}
	/*
	// xy
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {

		}
	}
	// xyz
	*/
	return res;
}

void print(const vector<int> &v) {
	for (int n: v) printf("%d, ", n);
	printf("\n");
}
int main() {
	// cout << isArmstrong(407) << endl;
	// cout << isArmstrong(704) << endl;
	assert(isArmstrong(0));
	assert(isArmstrong(1));
	assert(isArmstrong(407));
	assert(!isArmstrong(704));
	int num = 10;
	vector<int> v = findArmstrong(num);
	print(v);
	return 0;
}
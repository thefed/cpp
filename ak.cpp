#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;
int getMaxPow(int n) {
	int maxPower = INT_MAX / n;
	for (int i = 1; i < INT_MAX; i *= n) {
		if (i > maxPower) return i;
	}
	return 1;
}
// return is power of 5
bool isPow(int n) {
	int x = getMaxPow(5);
	return x % n == 0;
}
int getMin(string s) {
	int maxPower = getMaxPow(5);
	int n = s.size();

	// min num of splits into powers of 5
	vector<int> minSplits(n + 1, n);
	minSplits[0] = 0;

	for (int i = 1; i <= n; i++) {	// assumed num of splits
		for (int j = i; j >= 1; j--) {
			if (s[j - 1] == '0') continue;

			string end = s.substr(j - 1, i - j + 1);
			int num = stoi(end, NULL, 2);
			// printf("num=%d, ", num);
			if (maxPower % num == 0) {
				minSplits[i] = min(minSplits[i], minSplits[j - 1] + 1);
				// printf("i=%d, k=%d\n", i, minSplits[i]);
			}
		}
	}
	return minSplits[n] == n ? -1 : minSplits[n];
}

void test_split() {
	// assert(isPow(5));
	// assert(isPow(25));
	// assert(!isPow(20));
	// cout << getMaxPow(5);
	string s = "101101101";
	int res = getMin(s);
	cout << res << endl;
	assert(res == 3);

	assert(getMin("1111101") == 1);

	assert(getMin("00000") == -1);
}

int minMoves(vector < vector < int > > maze, int x, int y) {
	// cnt num of 2s
	int mazeCnt = 0;
	int m = maze.size(), n = maze[0].size();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (maze[i][j] == 2) mazeCnt++;
		}
	}


	return -1;
}

void test_maze() {
	vector<vector<int>> maze = {
		{0,2,0},
		{0,0,1},
		{1,1,1}};
	int x = 1, y = 1;
	int res = minMoves(maze, x, y);
	assert(res == 2);

	maze = {
		{0,1,0},
		{1,0,1},
		{0,2,2}};
	x = 1, y = 1;
	res = minMoves(maze, x, y);
	assert(res == -1);
}
void print(vector<float>& v) {
	for (float i : v) printf("%f ", i);
	printf("\n");
}
// round to 2 points
float roundTo(float x) {
	return round(x * 100) / 100;
}

float interpolateBtw(vector<int>& q, vector<float>&p, int x, int i) {
	// int n = q.size();
	int j = i + 1;
	float cost = p[j] + (p[j] - p[i]) * float(x - q[j]) / (float)(q[j] - q[i]);
	cost = roundTo(cost);
	return cost;
}

int findFirst(vector<int>& v, int x) {
	if (x == v[0]) return 0;
	int low = 0, high = v.size() - 1; 
	int mid;
	while (low + 1 < high) {
		mid = low + (high - low) / 2;
		if (x >= v[mid]) {
			low = mid;
		}
		else {
			high = mid - 1;
		}
	}
	return v[high] <= x ? high : low;
}

float interpolate(int n, vector <int>& quantity, vector <float>& price) {
	for (int i = 0; i < price.size(); i++) {
		if (price[i] <= 0.0) {
			price.erase(price.begin() + i);
			quantity.erase(quantity.begin() + i);
			i--;
		}
	}
	int size = quantity.size();
	if (quantity.size() == 1) return price[0];

	if (n < quantity[0]) {
		return interpolateBtw(quantity, price, n, 0);
	}
	else if (n > quantity[size - 1]) {
		return interpolateBtw(quantity, price, n, size - 2);
	}
	else {
		// find the 1st one that >= n in array
		int first = findFirst(quantity, n);
		if (quantity[first] == n) {
			return price[first];
		}
		else {
			// printf("not exists, first:%d\n",first);
			return interpolateBtw(quantity, price, n, first);
		}			
	}
}

void test_inter(){
	float x = roundTo(6.124);
	float y = 6.12;
	assert(x == y);
}
int main() {
	int n = 2000;
	vector<int> quantity = {10,25,50,100,500};
	vector<float> price = {27.32, 23.13,21.25, 18, 15.5};
	float res, exp;
	res = interpolate(n, quantity, price);
	
	exp = 6.13;
	assert(res == exp);

	n = 10;
	res = interpolate(n, quantity, price);
	assert(res == price[0]);

	n = 100;
	assert(interpolate(n, quantity, price) == price[3]);

	assert(findFirst(quantity, 125) == 3);
	assert(findFirst(quantity, 35) == 1);

	n = 30;
	exp = 22.75;
	res = interpolate(n, quantity, price);
	cout << res << endl;
	assert(res == exp);
	return 0;
}
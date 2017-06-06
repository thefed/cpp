//spiralMatrix.cpp, 

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
// LC 54
/*[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
*/
vector<int> spiralMatrix(vector<vector<int>> &matrix) {
	vector<int> res;
	const int m = matrix.size();
	if (m == 0) return res;
	const int n = matrix[0].size();
	if (n == 0) return res;

	int row_s = 0, row_e = m - 1, col_s = 0, col_e = n - 1;
	while (row_s <= row_e && col_s <= col_e) {
		// right
		for (int i = col_s; i <= col_e; i++) res.push_back(matrix[row_s][i]);
		row_s++;

		// down
		for (int i = row_s; i <= row_e; i++) res.push_back(matrix[i][col_e]);
		col_e--;

		// left, need to check row_e, otherwise, seg fault (matrix[row_e][i])
		if (row_s <= row_e) {
			for (int i = col_e; i >= col_s; i--) res.push_back(matrix[row_e][i]);
		}
		row_e--;

		// up, need to check col_s
		if (col_s <= col_e) {
			for (int i = row_e; i >= row_s; i--) res.push_back(matrix[i][col_s]);
		}
		col_s++;
	}
	return res;
}

// LC 59, spiral matrix ii
/*Given n = 3, You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]*/

vector<vector<int>> generateMatrix(int n) {
	if (n == 0) return vector<vector<int>> (); //matrix;

	vector<vector<int>> matrix(n, vector<int>(n));	// returned matrix
	// matrix.resize(m, vector<int>(n));
	int num = 1;	// first number to be filled
	int row_s = 0, row_e = n - 1, col_s = 0, col_e = n - 1;
	while (row_s <= row_e && col_s <= col_e) {
		for (int i = col_s; i <= col_e; i++) matrix[row_s][i] = num++;
		row_s++;	// right

		for (int i = row_s; i <= row_e; i++) matrix[i][col_e] = num++;
		col_e--;	// down

		if (row_s <= row_e) {	// left
			for (int i = col_e; i >= col_s; i--) matrix[row_e][i] = num++;
		}
		row_e--;

		if (col_s <= col_e) {	// up
			for (int i = row_e; i >= row_s; i--) matrix[i][col_s] = num++;
		}
		col_s++;
	}
	return matrix;
}

void print(const vector<int> &v) {
	for (int num: v) printf("%d, \n", num);
	printf("\n");
}

void test1() {
	vector<vector<int>> m = {
		{1, 2, 3 }, 
		{4, 5, 6}, 
		{7, 8, 9}
	};
	vector<int> exp = {1,2,3,6,9,8,7,4,5};
	vector<int> res = spiralMatrix(m);
	assert(exp == res);
}

void test2() {
	vector<vector<int>> m = {{1}};
	vector<int> exp = {1};//,2,3};//,6,9,8,7,4,5};
	vector<int> res = spiralMatrix(m);
	assert(exp == res);
}

void test3() {
	vector<vector<int>> m = {{1,2,3}};
	vector<int> exp = {1,2,3};//,6,9,8,7,4,5};
	vector<int> res = spiralMatrix(m);
	assert(exp == res);
}

// generate spiral matrix tests
void test_1() {
	vector<vector<int>> exp = {{1, 2, 3 },{8, 9, 4},{7, 6, 5}};
	int n = 3;
	vector<vector<int>> res = generateMatrix(n);
	assert(res == exp);
}

void test_2() {
	vector<vector<int>> exp = {{1}};
	int n = 1;
	vector<vector<int>> res = generateMatrix(n);
	assert(res == exp);
}

int main() {
	// spiralMatrix tests
	// test1();
	// test2();
	// test3();

	// generate spiral matrix
	test_1();
	test_2();
	return 0;	
}
// 5/28/17
#include <vector>
#include <iostream>
using namespace std;
/*
0 0 0 # # # 0 
0 0 # # 0 0 #
0 0 0 0 # # #
*/
void dfsTraverse(vector<vector<char>>& g, int i, int j, int& cnt, bool& horizontal, int level=0) {
	// check if i, j are valid
	if (i < 0 || i >= g.size() || j < 0 || j >= g[i].size() || g[i][j] != 'X') {
		return;
	}

	printf("visit [%d][%d] at level %d\n", i, j, level);

	g[i][j] = '#';
	cnt++;

	// traverse its neighbors

	// traverse left/right
	if (horizontal) {
		if (j < g[i].size() - 1) dfsTraverse(g, i, j + 1, cnt, horizontal, level + 1);
		if (j > 0) dfsTraverse(g, i, j - 1, cnt, horizontal, level + 1);
		if (cnt > 1) horizontal = true;	// horizontal traverse succeeds
		else horizontal = false;
	}

	if (!horizontal) {	// need up/down traversal
		if (i < g.size() - 1) dfsTraverse(g, i + 1, j, cnt, horizontal, level + 1);
		if (i > 0) dfsTraverse(g, i - 1, j, cnt, horizontal, level + 1);
	}
}

int getNumOfComponents(vector<vector<char>>& g) {
	// validate input not empty
	if (g.empty() || g[0].empty()) return 0;

	int m = g.size(), n = g[0].size();
	int count = 0;					 // num of connected components

	bool horizontal = true;
	int cnt = 0;
	// DFS traverse this graph
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (g[i][j] == 'X') {
				dfsTraverse(g, i, j, cnt, horizontal);
				if (cnt > 1) count++;	// count line segments with length >= 2
				// count++;
				cnt = 0;	// reset
				horizontal = true;
			}
		}
	}
	return count;
}
// 0 0 0 # # # 0 
// 0 0 # # 0 0 #
// 0 0 0 0 # # #

int main() {
	vector<vector<char>> g = {
		{'.', 'X', 'X', '.', 'X'},
		{'.', '.', 'X', 'X', 'X'},
		{'X', '.', 'X', 'X', 'X'}
	};

	int res = getNumOfComponents(g);
	printf("res:%d\n", res);
}

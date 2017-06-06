// hermes, 5/28/17
#include <iostream>
#include <vector>
using namespace std;
void paintDFS(vector<vector<int>>& g, int x, int y, int color, int originColor) {
	int m = g.size(), n = g[0].size();

	if (x < 0 || x >= m || y < 0 || y >= n || g[x][y] != originColor)  return;

	g[x][y] = color;
	// try up, down, left, right

	if (x > 0) paintDFS(g, x - 1, y, color, originColor);
	if (x < m - 1)	paintDFS(g, x + 1, y, color, originColor);

	if (y > 0) paintDFS(g, x, y - 1, color, originColor);
	if (y < n - 1) paintDFS(g, x, y + 1, color, originColor);
}	

// paint 0 to 2 from g[0][2]
/*
1 1 2 1 1 
1 2 2 2 1
1 1 2 2 1
*/ 

void paint(vector<vector<int>>& g, int x, int y, int color) {
 	int m = g.size(), n = g[0].size();

 	// DFS traverse to find all cells, and mark as target colors

 	int originColor = g[x][y]; /*getColor(g, x, y);*/
	paintDFS(g, x, y, color, originColor);
}

/*
return n1 > n2 ? n1 : n2;

n1 & n2
n1 = 3 //(0011)2
n2 = 5 //(0101)2

1 << i;

t = n1 - n2; // 2
// pick highest bit of t



// bolts[]
// nuts[]
// cmp(b, n) 
// return 0, 1 greater, -1 smaller

// 1 3 5 7 9 
// 2 4 6 8 10

// pick one from bolts, cmp with all nuts
// if smaller, put nuts in a smaller arrray
// if greater, put nuts in a larger array
// if equal, match

bolts[0] -> nuts[i] -> x=i
{equal: 1
smaller_nuts: 30
larger_nuts: 50
}// 4th

bolts[1]: cmp(b[0], n[i]) > 0 ? go to right child : go to left child
// create BST
// O(n^2)
*/
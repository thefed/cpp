#include<iostream>
#include<vector>
#include<cassert>
#include<queue>
using namespace std;

// number of islands using DFS
void DFS(vector<vector<char> > &grid, int i, int j) {
    // if invalid index or square, return 
    if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] != 'X') return;

    grid[i][j] = '0';	// mark as visited
    DFS(grid, i + 1, j);
    DFS(grid, i - 1, j);
    DFS(grid, i, j + 1);
    DFS(grid, i, j - 1);
}

int numIslands(vector<vector<char> > &grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int count = 0;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'X') {
                DFS(grid, i, j);
                count++;
            }
        }
    }
    return count;
}

void BFS(vector<vector<char> > &grid, int i, int j) {
    // use queue to store neighbors
    queue<vector<int> > q;
    q.push({i, j});
    grid[i][j] = '0';	// mark as visited

    // in this while loop, all neignboring nodes will be marked as "0"
    while (!q.empty()) {
        i = q.front()[0];
        j = q.front()[1];
        q.pop();

        // try all neighbors (up, down, left, rihgt)
        // add it to queue and mark as visited if valid
        if (i > 0 && grid[i - 1][j] == 'X') {
            q.push({i - 1, j});
            grid[i - 1][j] = '0';
        }
        if (i < grid.size() - 1 && grid[i + 1][j] == 'X') {
            q.push({i + 1, j});
            grid[i + 1][j] = '0';
        }
        if (j > 0 && grid[i][j - 1] == 'X') {
            q.push({i, j - 1});
            grid[i][j - 1] = '0';
        }
        if (j < grid[i].size() - 1 && grid[i][j + 1] == 'X') {
            q.push({i, j + 1});
            grid[i][j + 1] = '0';
        }
    }
}

// given a 2-D array, 'X' is island, '.' is water, find the number of connected component
int numIslandsBFS(vector<vector<char> > &grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int count = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'X') {
                BFS(grid, i, j);
                count++;
            }	
        }
    }
    return count;
}

void printGrid(const vector<vector<char> > &grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void createGrid(vector<vector<char> > &grid, string rows[]) {
    // initiate vector from string
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            grid[i][j] = rows[i][j];	
        }
    }
}

int main() {
    int m = 5; // rows
    int n = 10; // cols
    vector<vector<char> > grid(m, vector<char> (n));
    string rows[5] = {
        "X..XX....X", 
        "X.X...X.X.", 
        "XXX...X.XX", 
        "X.X..XX..X", 
        "..XX.X...X", 
    };

    createGrid(grid, rows);
    printGrid(grid);

    int numOfIslands = numIslands(grid);
    printf("numOfIslands: %d\n", numOfIslands);
    assert(numOfIslands == 5);

    // BFS solution
    createGrid(grid, rows);
    printGrid(grid);
    numOfIslands = numIslandsBFS(grid);
    printf("numOfIslands: %d\n", numOfIslands);
    assert(numOfIslands == 5);

    return 0;
}

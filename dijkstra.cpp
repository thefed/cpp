// 5/1/2017, impl dijkstra algorithm
// find shortest path from src to dest node in a graph
// 从无向图中找到从source到destination的最短路

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>
using namespace std;

// print decimal
#define printd(expr) printf(#expr " = %d\n", expr)

void print(const vector<int>& v, string msg="") {
    cout << msg;
    for (int n: v) printf("%d ", n);
    printf("\n");
}

void print(const vector<vector<int>>& v, string msg="") {
    cout << msg;
    for (auto &it : v) {
        for (int n : it) printf("%d ", n);
        printf("\n");
    }
    printf("\n");
}

vector<int> getPath(vector<int>& prevs, int src, int target) {
    vector<int> path;
    while (target != src && target != INT_MAX) {
        path.push_back(target);
        target = prevs[target];
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
    return path;
} 

vector<vector<int>> getPaths(vector<int>& prevs, int src) {
    vector<vector<int>> paths;
    for (int i = 0; i < prevs.size(); i++) {
        vector<int> path = getPath(prevs, src, i);
        paths.push_back(path);
    }
    return paths;
}

int minDistance(vector<int>& dist, vector<char>& visited) {
    int minDist = INT_MAX;
    int minId;
    for (int i = 0; i < dist.size(); i++) {
        if (!visited[i] && dist[i] < minDist) {
            minId = i;
            minDist = dist[i];
        }
    }
    return minId;
}

vector<int> dijkstra(vector<vector<int>>& g, int src) {
    assert(!g.empty() && !g[0].empty());
    const int n = g.size();         // num of nodes
    vector<char> visited(n, 0);     // 1: visited, 0: no yet
    vector<int> dist(n, INT_MAX);   // distance from [src] to others
    vector<int> paths(n, INT_MAX);  // previous node id of shortest path from [src] to [i] 

    // update src node
    dist[src] = 0;

    // while q is not empty
    for (int cnt = 0; cnt < n - 1; cnt++) {
        print(dist);
        // pick node [u] with min dist to src
        int u = minDistance(dist, visited);
        printf("add [%d]\n", u);
        assert(u >= 0 && u < n);

        // int target = 1;
        // if (u == target) return paths;

        // mark [u] as visited
        visited[u] = 1; 

        // check [u]'s neighbors, update dist vector
        for (int j = 0; j < n; j++) {
            if (!visited[j] && g[u][j] 
                && dist[u] != INT_MAX   // avoid overflow
                && dist[j] > dist[u] + g[u][j]) {
                dist[j] = dist[u] + g[u][j];
                paths[j] = u;
            }
        }
    }
    return paths;
}

int main() {
    //    4     3
    // 0 --- 1 ---- 2
    // |2   /1     /
    // 3 __/      /2
    // |1        /
    // 4________/
    vector<vector<int>> exp_paths = {
        {0},            // 0 -> 0
        {0,3,1},        // 0 -> 1
        {0,3,4,2},      // 0 -> 2
        {0,3},          // 0 -> 3
        {0,3,4},        // 0 -> 4
    };
    vector<vector<int>> graph = {
        {0,4,0,2,0},
        {4,0,3,1,0},
        {0,3,0,0,2},
        {2,1,0,0,1},
        {0,0,2,1,0}};
    int src = 0;
    vector<int> prevs = dijkstra(graph, src);
    vector<vector<int>> paths = getPaths(prevs, src);
    print(paths, "paths:\n");
    assert(paths == exp_paths);

    // test getPath: 0->1 => {0,3,1}
    vector<int> path0_1 = getPath(prevs, src, 1);
    print(path0_1, "path [0] -> [1]: ");

    // // test graph with a single node
    // vector<vector<int>> g2 = {{0}};
    // vector<int> prevs2 = dijkstra(g2, src);
    // vector<vector<int>> paths2 = getPaths(prevs2, src);
    // print(paths2);
    // assert(paths2 == (vector<vector<int>> {{0}}));
}
// input x, you can do 2 * x + 1 or 3 * x + 1, how many ways to reach a target result?
#include<iostream>
#include<assert.h>
using namespace std;
// time complexity: log(n, k)
void countPaths(int x, int target, int &res) {
    if (x == target) {
        res++;
        return;
    }
    else if (x > target) {   // can not reach target!
        return;
    }
    else {
        countPaths(2 * x + 1, target, res);
        countPaths(3 * x + 1, target, res);
    }
}

int getPaths(int x, int target) {
    int res = 0;
    countPaths(x, target, res);
    return res;
}   
int main() {
    //assert(getPaths(1, 1) == 0); 
    assert(getPaths(1, 7) == 1); 
    cout << getPaths(2, 100) << endl;
}

#include<iostream>
#include<vector>
using namespace std;
// TODO
// joseph circle, circular array or linked list impl?
// the user eats every other cookie from 1, (1..x), what the last one?
int getLast(int x) {
    vector<int> eaten(x + 1, 0);
    int prev = x;
    int curr = 1;
    for (int i = 1; i < x;i++) {  // need to eat x - 1 times
        if (!eaten[i]) {

        } 
    }
    return res;
}
int main() {
    return 0;
}

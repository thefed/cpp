#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

void print(const vector<int> &vec){
    for (int i = 0; i < vec.size(); i++) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}
int main() {
    // test swap
    int x = 4;
    int y = 5;
    swap(x, y);
    printf("x = %d, y = %d\n", x, y);

    vector<int> vec = {1, 2, 3, 4};
    swap(vec[0], vec[3]);
    print(vec);
}

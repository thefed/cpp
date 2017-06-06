#include<iostream>
#include<set>
#include<cassert>
using namespace std;
// check if n is a happy number: break it into digits, calc sum of their squars
// return true if it can reach 1; or false;
bool isHappy(int n) {
    set<int> myset;
    cout << n << " ";
    while (1) {
        int sum = 0;
        while (n > 0) {
            int remain = n % 10;
            sum += remain * remain;
            n /= 10;
        }
        cout << n << " ";
        if (sum == 1) return true;
        else if (myset.find(sum) == myset.end()) {
            n = sum;
            myset.insert(n);
        }
        else {
            return false;
        }
    }
    return false;
}
int main() {
    int n = 2;
    bool ret = isHappy(n);
    assert(!ret);
    return 0;
}

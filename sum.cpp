#include<iostream>
#include<assert.h>
using namespace std;

// add a + b, without using add/multiply
int sum(int a, int b) {
    while (b != 0) {
        int _a = a ^ b;
        int _b = (a & b) << 1;
#ifdef DE
        cout << "_a = " << _a << " _b = " << _b << endl;
#endif
        a = _a;
        b = _b;
    }
    return a;
}

int main() {
    int a = -5;
    int b = -6;
    cout << sum(a, b) << endl;

    cout << sum(3, 9) << endl;
}

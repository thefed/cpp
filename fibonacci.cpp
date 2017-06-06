// 4/25/2017, fibonacii optimization, time complexity from O(n) to O(logN)
// 
#include<iostream>
#include<assert.h>
#include<vector>
#include<ctime>
#include<climits>
using namespace std;
long fibonacci_n(int n) {
    if (n <= 2) {
        return 1;
    }
    long prev = 1;
    long next = 1;
    long curr = 1;
    for (int i = 2; i < n; i++) {
        next = curr + prev;
        prev = curr;
        curr = next;
    }
    return next;
}

void multiply(long f[2][2], long M[2][2]) {
    long x = f[0][0] * M[0][0] + f[0][1] * M[1][0];
    long y = f[0][0] * M[0][1] + f[0][1] * M[1][1];
    long z = f[1][0] * M[0][0] + f[1][1] * M[1][0];
    long w = f[1][0] * M[0][1] + f[1][1] * M[1][1];
    f[0][0] = x;
    f[0][1] = y;
    f[1][0] = z;
    f[1][1] = w;
}

// O(logN)
void matPower(long f[2][2], int n) {
    if (n <= 1) return;
    long M[2][2] = {{1,1}, {1,0}};    

    matPower(f, n / 2);
    multiply(f, f);
    if (n % 2 != 0) multiply(f, M);
}
// [1 1]n    [Fn+1 Fn  ] 
// [1 0]   = [Fn   Fn-1]
// 
long fibonacci(int n) {
    long f[2][2] = {{1,1}, {1,0}};
    if (n == 0) return 0;
    matPower(f, n - 1);
    return f[0][0];
}
// performance testing
void test_perf() {
    int N = 1000;
    //vector<int> nums = {5, 10, 20, 40, 80, 160, 320};
    vector<int> nums = {8, 16, 32, 64, 128, 256, 512};
    //int n = 39;
    for (int n: nums) {
    clock_t start = clock();
    for (int i = 0; i < N; i++) fibonacci_n(n);
    printf("O(N): %f ms.\n", 1000.0 * (clock() - start) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < N; i++) fibonacci(n);
    printf("O(log(N)): %f ms.\n", 1000.0 * (clock() - start) / CLOCKS_PER_SEC);
    long res = fibonacci(n);
        printf("n = %d, %ld\n\n", n, res);
    }
}
void test() {
    assert(fibonacci(1) == 1);
    assert(fibonacci(2) == 1);
    assert(fibonacci(3) == 2);
    assert(fibonacci(4) == 3);
    assert(fibonacci(5) == 5);
    assert(fibonacci(6) == 8);
    assert(fibonacci(7) == 13);

    int n = 39;
    cout << fibonacci(n) << endl;

    vector<int> nums = {1,1,2,3,5,8,13};
    for (int i = 0; i < nums.size(); i++) {
        assert(fibonacci(i + 1) == nums[i]);
    }
}
// test with function pointers
// long: return type, int: input parameter type
void test_ptr(long testFuncPtr(int)) {
    //long res = (*testFuncPtr)(2);
    //printf("res = %ld\n", res);
    vector<int> nums = {1,1,2,3,5,8,13};
    for (int i = 0; i < nums.size(); i++) {
        assert((*testFuncPtr)(i + 1) == nums[i]);
    }
}

int main() {
    // 1 1 2 3 5 8 13
    test();

    //test_perf();
    
    test_ptr(fibonacci_n);
    test_ptr(fibonacci);
    return 0;
}

// t2.cpp, practice use
// maxSubArray

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;

// return the max sum of subarray of given array
// array: [-2,1,-3,4,-1,2,1,-5,4] => 6
// dp   :  -2,1,-2,4, 3,5,6, 1,5
// dynamic solution: space O(N)
int maxSubArray(vector<int>& nums) {
    /*
    if (nums.empty()) return 0;
    
    int maxSum = nums[0];   // max value of sum
    int tmpMax = nums[0]; 	// tmp max sum until current iteration
    
    for (int i = 1; i < nums.size(); i++) {
        tmpMax = max(nums[i], tmpMax + nums[i]);    // end here vs start from here
        maxSum = max(maxSum, tmpMax);
    }
    
    return maxSum;
    */
    int n = nums.size();
    vector<int> dp(n, 0);   // dp[i]: max sum ending at position [i]
    dp[0] = nums[0];
    int maxSum = nums[0];
    for (int i = 1; i < n; i++) {
        dp[i] = nums[i] + (dp[i - 1] > 0 ? dp[i - 1] : 0);  // if previous [i-1]'s max sum < 0, start from [i]
        maxSum = max(maxSum, dp[i]);    // update max result
    }
    return maxSum;
}

// space O(1) dp
int maxSubArray_dpO1(vector<int>& nums) {
    if (nums.empty()) return 0;
    // as f[i] only depends on f[i - 1]
    int curMaxSum = nums[0];
    int prevMaxSum = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        prevMaxSum = max(nums[i] + prevMaxSum, nums[i]);
        curMaxSum = max(curMaxSum, prevMaxSum);
    }
    return curMaxSum;
}

void test(int f(vector<int>&), vector<int>& nums, int exp, string msg) {
    cout << msg << endl;
    int res = (*f)(nums);
    assert(res == exp);
}

int main() {
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    int exp = 6;
    test(maxSubArray, nums, exp, "dp O(N) space");
    test(maxSubArray_dpO1, nums, exp, "dp O(1) space");
	return 0;
}
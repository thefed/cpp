#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
int getLowerBound(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] >= target) {
            right = mid;
        }
        else { // test: 1 2 4 5 -> find 3
            left = mid + 1;
        }
    }
    return nums[left] == target ? left : -1;
}

int getUpperBound(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (nums[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid;
        }
    }
    return nums[right] == target ? right : (nums[left] == target ? left : -1);
    // test: 1 2 3 3 4 5 -> find 3
    // l=0, r=5, m=2, ==
    // l=2, r=5, m=3, ==
    // l=3, r=5, m=4, >
    // l=3, r=3, exit
    
    // 5 7 7 8 8 10 -> find 8
    // l=0,r=5,m=2, < 8
    // l=3,r=5,m=4, == 8
    // l=5,r=5, exit
}
vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> res(2, -1);
    
    // search for lower bound
    res[0] = getLowerBound(nums, target);
    
    // if no lower bound, then no upper bound either
    if (res[0] != -1) { // search for upper bound
        res[1] = getUpperBound(nums, target);
    }
    return res;
}

int main() {
    vector<int> nums = {5, 7, 7, 8, 8, 10};
    vector<int> res = searchRange(nums, 8);
    assert(res[0] == 3);
    assert(res[1] == 4);
    return 0;
}
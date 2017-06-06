// containDulicate 3: |nums[i] >= -3|
// 

#include <iostream>
#include <climits>
#include <cassert>
#include <set>
#include <vector>
using namespace std;
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    // maintain a set of size k
    /**
     * [2147483647,-2147483647]
        1 (k)
        2147483647 (t)
     */
    // to handle overflow
    set<long> window; // set is ordered automatically 
    for (int i = 0; i < nums.size(); i++) {
        if (i > k) window.erase(nums[i-k-1]); // keep the set contains nums i j at most k
        // |x - nums[i]| <= t  ==> -t <= x - nums[i] <= t;
        // cout << x << endl;
        auto pos = window.lower_bound((long)nums[i] - t); // x-nums[i] >= -t ==> x >= nums[i]-t 
        // x - nums[i] <= t ==> |x - nums[i]| <= t    
        if (pos != window.end() && *pos - (long)nums[i] <= t) return true;
        window.insert(nums[i]);
    }
    return false;
}
// debug print macro
#define dprint(expr) printf(#expr " = %d\n", expr)
int main() {
	// printf("%d, %d\n", INT_MIN, INT_MAX);
	dprint(INT_MIN);
	dprint(INT_MAX);
	dprint(INT_MIN - INT_MAX);
	dprint(INT_MAX - INT_MIN);
	// // check overflow
	// printf("%d\n", INT_MIN - INT_MAX);	// =1

	// printf("%d\n", INT_MAX - INT_MIN);	// =-1
	vector<int> nums = {INT_MAX, INT_MIN};
	int k = 1;
	int t = INT_MAX;
	bool b = containsNearbyAlmostDuplicate(nums, k, t);
	assert(!b);
	return 0;
}

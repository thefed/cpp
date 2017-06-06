// Adobe hackathon challenge

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
void swapVec(vector<int> &nums, int i, int j) {
	int tmp = nums[i];
	nums[i] = nums[j];
	nums[j] = tmp;
}

// swap the indices...
void swap(map<int, int> &odds, map<int, int> &evens, vector<int> &nums, const map<int, int>::iterator &it, int targetIndex) {
    // swap (val=1, id=2) and (val=2, id=0), in 1st iteration, targetIndex = 0
    // it=(1, id=2), need to locate (val, id=0)
    int  val= nums[targetIndex];  // val(x) = 2
    
    // check the element to be swaped, if even, update evens table, otherwise, update odds table
    if (val % 2 == 0) {   // even number, must be in evens table
        evens[val] = it->second;    // set to 2
    }
    else {
        odds[val] = it->second;
    }
    // check it->first to decide it is in odds or evens
    if (it->first % 2 == 1) {
        odds[it->first] = targetIndex;
    }
    else {
        evens[it->first] = targetIndex;
    }

    swapVec(nums, it->second, targetIndex);
}   

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    // first, sort the odd-value and even-value elements 
    int n = 4;
    //cin >> n;
    // vector<int> nums(n);
    vector<int> nums = {2, 3, 1, 4};
    vector<int> res(n); // result
    int cnt = 0;    // number of swaps needed
    for (int i = 0; i < n; i++) {
            //cin >> nums[i];
    }

    map<int, int> evens;    // (value, index)
    map<int, int> odds;
    for (int i = 0; i < n; i++) {
        if (nums[i] % 2 == 0) evens[nums[i]] = i;
        else odds[nums[i]] = i;
    }
    // 1st element should be taken from odds table, 2nd should be taken from evens table
    // if current index table[nums[i]] does not match the expected i, then swap
    map<int, int>::iterator it1 = odds.begin(), it2 = evens.begin();
    int i = 0;
    while (it1 != odds.end() || it2 != evens.end()) {
        // place an odd element in the result        
        if (it1->second != i) {
            // swap
            swap(odds, evens, nums, it1, i);
            cnt++;
        }
//        else, put it in the result
        
        res[i++] = it1->first;
        it1++;
        // place an even element in the result
        if (it2->second != i) {
            // swap
            swap(odds, evens, nums, it2, i);
            cnt++;
        }
        
        res[i++] = it2->first;
        it2++;
    }
    // 2 3 1 4 
    // odds: (3, 1), (1, 2); evens: (2, 0), (4, 3)
    // swap (1, id=2) <-> (2, id=0)
    // 1's index is 2, should be 0, look up the element with index 0, found (id=0, val=2), swap them
    // 1 3 2 4
    // 1 2 3 4
    
    // print out the result vector
    for (int i = 0; i < n; i++) cout << res[i] << " ";
    cout << endl << cnt << endl;
    return cnt;
}

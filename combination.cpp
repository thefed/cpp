#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;

void combinationSum(std::vector<int> &candidates, int target, std::vector<std::vector<int> > &res, std::vector<int> &combination, int begin) {
    if  (target == 0) {
        cout << "tmpRes: " << combination.size() << endl;
        res.push_back(combination);
        return;
    }
    for (int i = begin; i < candidates.size() && target >= candidates[i]; ++i) {
        combination.push_back(candidates[i]);
        combinationSum(candidates, target - candidates[i], res, combination, i);
        combination.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> combination;
    combinationSum(candidates, target, res, combination, 0);
    return res;
}

int main() {
    vector<int> nums = {8, 7, 4, 3};
    int target = 11;
    // expected: [[3,4,4],[3,8],[4,7]]
    vector<vector<int> > res = combinationSum(nums, target);
    cout << res.size() << endl;
    assert(res.size() == 3);
    return 0;
}

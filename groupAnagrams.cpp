#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cassert>
#include <set>  // multiset stores ordered elements
using namespace std;
class Solution {
    public:
        vector<vector<string>> groupAnagrams(vector<string>& strs) {
            vector<vector<string>> res;
            unordered_map<string, multiset<string>> mp;
            for (string s : strs) {
                string t = s;
                sort(t.begin(), t.end());
                mp[t].insert(s);
            }
            for (auto m : mp) {
                vector<string> anagram(m.second.begin(), m.second.end());
                res.push_back(anagram);
            }
            return res;
        }
};
void print(const vector<vector<string>> &v) {
    for (auto &it: v) {
        for (string s : it) {
            cout << s << ", ";
        }
        cout << endl;
    }
    cout << endl;
}
int main() {
    Solution sol;
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> res = sol.groupAnagrams(strs);
    vector<vector<string>> exp = {{"ate", "eat","tea"},
        {"nat","tan"},
        {"bat"}};
    print(res);
    sort(res.begin(), res.end());
    sort(exp.begin(), exp.end());
    assert(res == exp);
    return 0;
}

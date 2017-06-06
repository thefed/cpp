// LC 139, word break(able)
//
#include<iostream>
#include<string>
#include<cassert>
#include<vector>
using namespace std;
bool wordBreak(string &s, vector<string> &wordDict) {
    vector<char> dp(s.size() + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= s.size(); i++) {
        string curr = s.substr(0, i);
        // check if "l", "le", "lee", "leet", "leetc" is breakable or not...
        for (int j = 0; j < wordDict.size(); j++) {
            int len = wordDict[j].size();
            //printf("i = %d, j = %d\n", i, j);
            //if (curr == wordDict[j]) { dp[i] = 1; break; }
            // check if curr can be split into a breakable str + postfix (word)
            if (len <= i && dp[i - len] && curr.substr(i - len) == wordDict[j]) {
                dp[i] = 1;
                cout << "breakable: " << curr << endl;
                break; 
            }
         }
    }
    return dp[s.size()];
}

int main() {
    string s = "leetcode";
    //vector<string> wordDict = {"code", "leet"};
    vector<string> wordDict = {"leet", "code"};
    assert(wordBreak(s, wordDict));
    return 0;
}


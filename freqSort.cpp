#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <cassert>
using namespace std;
// sort chars in the given string by char freq (descending)
string frequencySort(string s) {
    string res;
    unordered_map<char, int> map;
    for (char c : s) map[c]++;
    priority_queue<pair<int, char> > pq;
    for (auto it = map.begin(); it != map.end(); it++) {
        pq.push(make_pair(it->second, it->first));  // {freq, item}
    }
    while (!pq.empty()) {
        int freq = pq.top().first;
        char c = char(pq.top().second);
        res += string(freq, c);
        pq.pop();
    }
    return res;
}

int main() {
    string s = "tree";
    string res = frequencySort(s);
    assert(res == "eert" || res == "eetr");

    s = "abbcccdddd";
    res = frequencySort(s);
    cout << res << endl;
    assert(res == "ddddcccbba");
    return 0;
}

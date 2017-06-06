// 4/12/2017, find top k frequent elements in an array using priority queue

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<cassert>
using namespace std;

void printQ(priority_queue<pair<int, int> > pq) {
    printf("(freq, item)\n");
    while (!pq.empty()) {
        int freq = pq.top().first;
        int val = pq.top().second;
        pq.pop();
        printf("(%d:%d), ", freq, val);
    }
    printf("\n");
}
// use bucket sort
vector<int> topKFrequent_bucket(vector<int>& nums, int k ) {
    vector<int> res;
    unordered_map<int, int> map;
    for (int i : nums) map[i]++;

    int n = nums.size();
    vector<vector<int>> bucket(n + 1, vector<int>());
    for (auto it = map.begin(); it != map.end(); it++) {
        bucket[it->second].push_back(it->first);
    }

    // add items to result
    for (int i = bucket.size(); i > 0 && res.size() < k; i--) {
        res.insert(res.end(), bucket[i].begin(), bucket[i].end());
    }
    return res;
}

// priority queue
vector<int> topKFrequent(const vector<int> &nums, int k) {
    vector<int> res;
    unordered_map<int, int> map;
    for (int num : nums) map[num]++;
    priority_queue<pair<int, int> > pq;
    for (auto it = map.begin(); it != map.end(); it++) {
       // {freq, item}
       pq.push(make_pair(it->second, it->first)); 
       printf("(%d: %d) added\n", it->second, it->first);

       // if add items to result now, the order will not be kept
//       if (pq.size() > map.size() - k) {
//            res.push_back(pq.top().second);
//            pq.pop(); 
//       }
    }
    printQ(pq);
    while (k > 0) { res.push_back(pq.top().second); pq.pop(); k--; }
    return res;
}

void print(const vector<int> &v) {
    for (int it : v) printf("%d ", it);
    printf("\n");
}

int main() {
    vector<int> nums = {1,1,1,1,2,2,3,4, 5,5,5,5};
    int k = 2;
    vector<int> res = topKFrequent(nums, k);
    print(res);
    vector<int> exp = {5, 1};
    assert(res == exp);

    res = topKFrequent_bucket(nums, k);
    print(res);
    assert(res == exp);
}

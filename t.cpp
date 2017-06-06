// t.cpp, for practice use only
// meridianlink
// 1. impl pq; AVL tree;
// 2. contains duplicate 1/2/3
// 3. linked list cycle detection

#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
using namespace std;

// e.g. return the 3rd largest item
// find a top k item in a linked list
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(NULL) {}
};

void print(ListNode *head) {
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int topKList(ListNode* head, int k) {
    priority_queue<int, vector<int>, std::greater<int>> q;
    while (head) {
        q.push(head->val);
        if (q.size() > k) q.pop();
        head = head->next;
    }
    return q.top();
}

ListNode* getKth(ListNode* head, int k) {
    ListNode *cur = head;
    assert(k >= 0);
    while (k > 0) {
        cur = cur->next;
        k--;
    }
    return cur;
}

int partition(ListNode *head, ListNode* end) {
    ListNode *cur = head;
    ListNode *pivot = end;
    int i = 0;
    ListNode *start = head;
    while (cur != pivot) {
        // mv greater items to the left of pivot
        if (cur->val >= pivot->val) {
            // swap(nums[i], nums[j]);
            swap(start->val, cur->val);
            start = start->next;
            i++;
        }
        cur = cur->next;
    }
    swap(start->val, pivot->val);
    // printf("pivot_id: %d\n", i);
    return i;
}

// quick sort, use partition
int topKList_qs(ListNode* head, int k) {
    ListNode *end = head;

    int len = 1;
    while (end->next) { end = end->next; len++;}
    assert(len >= k);

    ListNode *start = head;
    while (true) {
        int pivot_id = partition(start, end); 
        if (pivot_id == k - 1) return getKth(start, k - 1)->val;
        else if (pivot_id > k - 1) end = getKth(start, pivot_id - 1);
        else {
            start = getKth(start, pivot_id + 1);
            k -= (pivot_id + 1);    // found p+1 items
        }
    }
}

// n: num of nodes to insert from head
ListNode* createList(ListNode* head, int n) {
    for (int i = n; i >= 1; i--) {
        ListNode *node = new ListNode(i);
        node->next = head;
        head = node;
    }
    return head;
}

void deleteList(ListNode *head) {
    while (head) {
        ListNode *node = head;
        head = head->next;
        delete node;
    }
}

void test(int f(ListNode*, int), ListNode* head, int k, int exp, string msg="") {
    cout << msg;
    int res = (*f)(head, k);
    assert(res == exp);
}
void test_topK() {
    int n = 6;  // create a linked list 1..6
    int k = 3;
    int exp = 4;    // expected top k
    ListNode *head = NULL;
    head = createList(head, n);
    print(head);

    test(topKList, head, k, exp);
    deleteList(head);

    head = NULL;
    head = createList(head, n);
    print(head);
    test(topKList_qs, head, k, exp);
    deleteList(head);
}

// check if list has cycle
bool hasCycle(ListNode* head) {
    if (!head || !head->next) return false;
    ListNode *fast = head, *slow = head;
    // while (fast->next && fast->next->next) {
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) return true;
    }
    return false;
}

// proof:
// +-- a --+- b -+ ("fast" and "slow" meet at 6)
// 0 1 2 3 4  5  6
//         |_____|
// let "slow" move x steps, "fast" move 2*x steps, and meet
// then x = a + b, 2x = a + b + k*len (len: cycle length: 3)
// then let "entry" move a steps, where a = k*len - b
// "entry" will reach cycle start position, so does "slow"
// as "slow" is at position b (after cycle start), b + a = k*len, reach start


// return the node where the cycle begins
ListNode* detectCycle(ListNode *head) {
    if (!head || !head->next) return NULL;
    ListNode *fast = head, *slow = head, *entry = head; // cycle entry position
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            while (slow != entry) {
                slow = slow->next;
                entry = entry->next;
            }
            return entry;
        }
    }
    return NULL;
}

void test_cycle() {
    int n = 6;
    ListNode *head = createList(NULL, n);
    assert(!hasCycle(head));

    ListNode *tail = getKth(head, n - 1);
    int k = 3;  // link tail [5] with node [2]
    tail->next = getKth(head, k - 1);
    // 1 2 3 4 5 6
    //     |_____|

    assert(hasCycle(head));

    ListNode *cycleStart = detectCycle(head);
    assert(cycleStart);
    assert(cycleStart->val == getKth(head, k - 1)->val);
}

bool wordPattern(string pattern, string str) {
    if (pattern.empty() || str.empty()) return true;
    unordered_map<char, string> map;
    unordered_set<string> set;
    int i = 0;
    stringstream ss(str);
    string word;
    while (getline(ss, word, ' ')) {
        if (!word.empty()) {
            if (i == pattern.size()) return false;
            if (map.find(pattern[i]) == map.end() && set.count(word) == 0) {
                map[pattern[i]] = word;
                set.insert(word);
            }
            else if (map[pattern[i]] != word) return false;
            i++;
        }
    }
    return i == pattern.size();
}

void test_word() {
    string pattern = "aaa";
    string str = "aa aa aa aa";
    bool res = wordPattern(pattern, str);
    assert(!res);
}

vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    // m items in nums1, n items in nums2 => m x n pairs in total: [0,1,2,...,mn-1]
    
    // pairs[k] = nums1[k/n] + nums2[k % n]
    // store {key=sum, val=k} in min-priority queue
    priority_queue<pair<int, int>> q;
    const int m = nums1.size(), n = nums2.size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            q.push({nums1[i] + nums2[j], i * n + j});
            if (q.size() > k) q.pop();
        }
    }
    if (k > q.size()) k = q.size();
    k = 0;
    vector<pair<int, int>> res(k);
    int id = 0;

    while (!q.empty()) {
        pair<int, int> it = q.top();
        printf("key=%d, i = %d, j = %d\n", it.first, it.second / n, it.second % n);
        res[k - 1 - id] = {nums1[it.second / n], nums2[it.second % n]};
        id++;
        q.pop();
    }
    return res;
}

void test_pair() {
    vector<int> nums1 = {1,7,11}, nums2 = {2,4,6};
    vector<pair<int, int>> exp = {{1,2},{1,4},{1,6}};
    int k = 3;
    vector<pair<int, int>> res = kSmallestPairs(nums1, nums2, k);
    assert(res == exp);
}

int main() {
    // test_topK();

    // test_cycle();

    // test_word();

    test_pair();
    return 0;
}
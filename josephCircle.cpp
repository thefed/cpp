// given candies 1~n, eat #1, then #3, then #5, what is the last candy left? (josephus, k=2)
// similar to josephus circle: kill every k-th person, find the safe position (the last remaining position)
// josephus: f(n, k) = (f(n - 1, k) + k - 1) % n + 1, f(1) = 1
// f(n,k) means the safe/last position given nodes 1~n, kill every k-th node (k >= 1)
#include <iostream>
#include <vector>
#include <cassert>
#include <string>

using namespace std;
// 1 2 3 4 5 6 7 8
// x   x   x   x
//   2   4   6   8
//   x       x
//       4      8
//       x
//              8
// method 1: circular array
int getLast(vector<int>& nums) {
    int start = 0;  // index of the first item to rm
    const int n = nums.size();
    for (int i = 0; i < n - 1; i++) {   // rm n-1 items
        // rm it
        printf("rm %d\n", nums[start]);
        nums[start] = 0;
        // mv start to the next position to be deleted
        int j = 2;
        while (j > 0) {
            start = (start + 1) % n;
            if (nums[start] > 0) {
                j--;
            }
        }
    }
    return nums[start];
}

// method 2: circular linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
// create a circular linked list from items
ListNode* createList(vector<int>& items) {
    if (items.empty()) return NULL;
    ListNode preHead(0);
    ListNode *tail = &preHead;
    for (int item : items) {
        tail->next = new ListNode(item);
        tail = tail->next;

    }
    // link back to head
    tail->next = preHead.next;
    return preHead.next;
}
// 1 2 3 4 5 6 7 8
// |_____________|
//   2 3 4 5 6 7 8
//   |___________|
int getLast(ListNode *head) {
    assert(head);
    if (!head->next) return head->val;

    // find end of list
    ListNode *curr = head;
    while (curr->next != head) {
        curr = curr->next;
    }
    // rm a node by 'prev->next'
    // to relink tail and head->next when head node is deleted firstly
    ListNode preHead(0);
    preHead.next = curr;    // 8
    ListNode *prev = &preHead;
    prev = prev->next;  // mv prev to 8, now prev->next is 'head'

    while (prev->next->next != prev->next) {
        ListNode *deleted = prev->next;
        // rm prev->next, relink it
        prev->next = prev->next->next;
        // mv it two steps forward
        prev = prev->next;
        printf("rm list node: %d, prev: %d\n",  deleted->val, prev->val);
        delete deleted;
    }
    return prev->next->val; // only 'prev->next' remained
}

void print(vector<int>& v, string msg="") {
    cout << msg;
    for (int i : v) printf("%d ", i);
    printf("\n");
}

// f(n, k): last position, rm every k-th node starting from position 1
// e.g. 1 2 3 4 5, k=3, rm 1st 3-th node (started from position 1)
//      1 2 x 4 5, k=3, rm 2nd 3-th node (started from position 4)
//      1 2 3 4, f(5-1, k=3) returns the safe position 'idx' (started from positon 1)
//      use f(4,k=3)'s result, shifting this safe position from 1 to 4, => (safe_idx + k - 1) % n + 1
// rm k-th person, n - 1 nodes left, now f(n - 1, k) means: last position, rm nodes from k-th position
int joseph(int n, int k) {
    if (n == 1) return 1;

    return (joseph(n - 1, k) + k - 1) % n + 1;
}

int joseph2(int n, int k) {
    if (n == 1) return 1;

    int res = 0;
    for (int i = 2; i <= n; i++) {
        res = (res + k) % i;
    }
    return res + 1;
}

int main() {
    vector<int> nums = {1,2,3,4,5,6,7};
    print(nums, "initial nodes: ");

    ListNode *head = createList(nums);
    int last = getLast(nums);
    printf("last: %d\n", last);

    last = getLast(head);
    printf("last: %d\n", last); // 6
    
    // get last using joseph
    int n = nums.size(), k = 2; // equivalent to (n=7,k=2)'s joseph
    int pos = joseph(n, k);     // note that joseph deletes node, counting from position 1
    // adjust index, mv pos backward by k-1 steps, equivalent to mv forward n - k + 1 steps
    // relative distance from position 1 to safe position: pos - 1
    last = (pos - 1 + n - k + 1) % n + 1;
    printf("last: %d\n", last); // 6

    int safePos = joseph(5, 2); // 3
    printf("safePos = %d\n", safePos);

    safePos = joseph2(5, 2);
    printf("safePos = %d\n", safePos);
    return 0;
}

// linked list practice
// 5/3/2017, simplified it
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int val, ListNode *next=NULL): val(val), next(next){}
};

void print(ListNode *head, string msg="") {
	cout << msg;
    if (!head) {
        printf("empty\n");
        return;
    }
    ListNode *cur = head;
    while (cur) {
        printf("%d ", cur->val);
        cur = cur->next;
    }
    printf("\n");
}

// insert a list node from the head
ListNode* insert(ListNode *head, int item) {
    ListNode *node = new ListNode(item);
    node->next = head;
    head = node;
    return head;
}

// return the head of result list
ListNode* deleteListNode(ListNode *head, int val) {
    if (!head) return NULL;
    printf("Deleting %d\n", val);
    ListNode dummy(0);
    dummy.next = head;
    ListNode *curr = &dummy;
    // 1,1,1,1,1,1, delete 1, return NULL
    // cn
    // 1,2,3,1, delete 1, return node 2
    while (curr) {
        if (curr->next && curr->next->val == val) {
            ListNode *deleted = curr->next;
            curr->next = curr->next->next;
            delete deleted;
            // print(curr->next);
        }
        else {
            curr = curr->next;
        }
    }
    return dummy.next;
}

void deleteList(ListNode *head) {
    while (head) {
        ListNode *node = head;
        head = head->next;
        delete node;
    }
}

ListNode* findKth(ListNode* head, int k) {
    ListNode *curr = head;
    while (k > 0) {
        if (!curr) { 
            printf("invalid k = %d\n", k); 
            return NULL; 
        }
        curr = curr->next;
        k--;
    }
    return curr;
}

// reverse linked list in place
// 1->2->3->NULL => 3->2->1->NULL
ListNode* reverseLinkedList(ListNode *head) {
    ListNode *prev = NULL;
    ListNode *curr = head;		// current node
    while (curr) {
        ListNode *temp = curr->next;
        curr->next = prev;	// 1 -> NULL
        prev = curr;		// save curr (next loop's "next" field value)
        curr = temp;		// move h forward
    }
    return prev;			// last node of input linked list
}	

// general way to reverse any linked list sequence
ListNode *reverse(ListNode *head) {
	ListNode *prev = NULL;
	ListNode *curr = head;
	// similar to insert a node from head(prev)
	// N 1 2 3 4 5 
	// p c n
	//   2 1 3 4 5
	//   p c  
	//   ...
	//           p c
	// treat prev as 'head', each time, insert 'curr' from 'prev'
	while (curr) {
		ListNode *next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return prev;
}

// general way to reverse between
ListNode* reverseBtw_g(ListNode *head, int m, int n) {
	// mv head to position [m-1]
	// 1 2 3 4 5 6 7, m=2,n=4
	// p c n
	// p c   n
	ListNode preHead(0);
	preHead.next = head;
	ListNode *prev = &preHead;
	for (int i = 0; i < m - 1; i++) {
		prev = prev->next;
	}
	ListNode *curr = prev->next;
	ListNode *next = curr->next;
	// mv n - m - 1 times: m=2,n=1, 2 rounds is enough
	for (int i = 0; i < n - m; i++) {
		curr->next = next->next;	// save "next"'s next
		
		// mv "next" to front
		next->next = prev->next;
		prev->next = next;

		next = curr->next;			// mv "next" forward
	}
	return preHead.next;
}

ListNode* reverseBetween(ListNode* head, int m, int n) {
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *temp = dummy;
    assert(temp);
    ListNode *prevMth = findKth(temp, m - 1);
    assert(prevMth);
    assert(prevMth->val == 1);

    ListNode *mth = prevMth->next;
    temp = dummy;
    ListNode *nth = findKth(temp, n);
    assert(nth->val == 4);

    ListNode *nextNth = nth->next;
    nth->next = NULL;

    reverseLinkedList(mth);
    prevMth->next = nth;
    mth->next = nextNth;
    ListNode *newHead = dummy->next;
    delete dummy;
    return newHead;
}

// 1 2 3 4 5
// if k=2, => 2 1 4 3 5
// if k=3, => 3 2 1 4 5 (if the num of remainint items are less than k, keep them)
ListNode* reverseKGroup(ListNode *head, int k) {
	if (k == 1 || !head) return head;
	int len = 0;	// length of the list
	ListNode *curr = head;
	while (curr) {
		len++;
		curr = curr->next;
	}
	k %= len;		// simplify k
	ListNode preHead(0);
	preHead.next = head;
	ListNode *prev = &preHead, *next;
	while (len >= k) {
		curr = prev->next;	// pointing to node 1
		next = curr->next;
		for (int i = 0; i < k - 1; i++) {
			curr->next = next->next;	// save "next"'s next
			// mv "next" to front
			next->next = prev->next;
			prev->next = next;
			// mv "next" forward
			next = curr->next;	
		}
		prev = curr;			// point to node 1, now node 1 is the end of current k range group
		len -= k;
	}
	return preHead.next;
}

// merge two lists, return the sorted list
ListNode* mergeTwoLists(ListNode *list1, ListNode *list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    ListNode dummy(0);
    ListNode *tail = &dummy;

    while (list1 && list2) {
        if (list1->val < list2->val) {
            tail->next = list1;
            list1 = list1->next;
        }
        else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    tail->next = list1 == NULL ? list2 : list1;
    return dummy.next;
}

ListNode *createList(const vector<int>& nums) {
    ListNode *head = NULL;
    for (int i = nums.size() - 1; i >= 0; i--) head = insert(head, nums[i]);
    return head;
}

vector<int> getItems(ListNode *head) {
    vector<int> items;
    while (head) {
        items.push_back(head->val);
        head = head->next;
    }
    return items;
}

/*
// 1,1,1,1,1,1, delete 1, return NULL
    // cn
    // 1,2,3,1, delete 1, return node 2
    while (curr) {
        if (curr->next && curr->next->val == val) {
            ListNode *deleted = curr->next;
            curr->next = curr->next->next;
            delete deleted;
            // print(curr->next);
        }
        else {
            curr = curr->next;
        }
    }
*/

ListNode* deleteByArray(ListNode *head, vector<int>& array) {
    printf("delete by array\n");
    ListNode preHead(0);
    preHead.next = head;
    ListNode *curr = &preHead;
    int j = 0;
    // {1,2,3,1} [1,3]
    for (int i = 0; i < array.size(); i++) {
        // [0], j=0
        // if (array[i] == j) curr = curr->next;
        for (; j < array[i] - 1; j++) {
            curr = curr->next;
        }
        curr->next = curr->next->next;
    }
    return preHead.next;
}

void test_insert_delete() {
    int item = 1;
    int count = 6;
    // 1,1,1,1,1,1, delete 1 => NULL
    vector<int> nums(count, item);
    ListNode *head = createList(nums);
    print(head);
    assert(head);
    ListNode *result = deleteListNode(head, item);
    print(result);  // should be empty
    assert(!result);
    assert(getItems(result).empty());
    deleteList(result);

    // list: 1,2,3,1, delete 1 => 2,3
    vector<int> items = {1,2,3,1};
    head = NULL;
    head = createList(items);
    print(head);
    assert(head);
    result = deleteListNode(head, item);
    print(result);
    assert(getItems(result) == (vector<int> {2,3}));
    deleteList(result);


    // {1,2,3,1};
    vector<int> array = {1,3};
    head = createList(items);
    result = deleteByArray(head, array);
    print(result);
    assert(getItems(result) == (vector<int> {1,3}));
    deleteList(result);
}

void test_merge() {
    vector<int> nums1 = {2,4,6,8};
    vector<int> nums2 = {1,3,7,9};
    // expected merged result list
    vector<int> nums = {1,2,3,4,6,7,8,9};
    ListNode *p = createList(nums1);
    ListNode *q = createList(nums2);    
    ListNode *merged = mergeTwoLists(p, q);
    print(merged);
    assert(getItems(merged) == nums);
    deleteList(merged);
}

void test_reverse() {
    vector<int> items = {1,2,3,4,5,6,7};
    ListNode *head = createList(items);
    ListNode *res = reverseLinkedList(head);
	vector<int> items_r = items;	// revered items
    reverse(items_r.begin(), items_r.end());
    assert(getItems(res) == items_r);

	res = reverse(res);
	assert(getItems(res) == items);

    // reverse btw
	int m = 2, n = 4;
    res = reverseBetween(res, m, n);
	vector<int> items_exp = {1,4,3,2,5,6,7};
	print(res, "reversed btw node 2 to 4: ");
	assert(getItems(res) == items_exp);

	res = reverseBtw_g(res, m, n);
	print(res, "reversed btw node 2 to 4: ");
	assert(getItems(res) == items);	// restore affected range

	int k = 2;
	res = reverseKGroup(res, k);
	print(res, "reverse 2-group: ");
	assert(getItems(res) == (vector<int> {2,1,4,3,6,5,7}));

	k = 3;
	deleteList(res);
	res = createList(items);
	res = reverseKGroup(res, k);
	print(res, "reverse 3-group: ");
	assert(getItems(res) == (vector<int> {3,2,1,6,5,4,7}));
	deleteList(res);
}

int main() {
    test_insert_delete();

    test_merge();

    test_reverse();
    return 0;
}

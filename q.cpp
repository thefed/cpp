// q.cpp, impl priority queue using heap 
// 5/3/2017
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;

class PriorityQueue {
private:
	vector<int> pq_keys;	// container of the keys in prioriry queue

	// max index need < high
	void heapify(int high, int root) {
		while ((2*root + 1) < high) {
			int left = 2 * root + 1;	// left child index
			int right = 2 * root + 2;	// right child index
			int largest = root;	// index of the largest element
			if (pq_keys[left] > pq_keys[largest]) largest = left;
			if (right < high && pq_keys[right] > pq_keys[largest]) largest = right;
			if (largest != root) {
				// mv greater item up, smaller item down
				swap(pq_keys[largest], pq_keys[root]);
				root = largest;
			}
			else break;
		}
	}

	void leftShift(int low, int childIdx) {
		// get parent index from child index
		while (childIdx > low) {
			int parentIdx = (childIdx - 1) / 2;
			if (pq_keys[parentIdx] < pq_keys[childIdx]) {
				swap(pq_keys[parentIdx], pq_keys[childIdx]);
				childIdx = parentIdx;
			}
			else break;
		}
	}

	void buildHeap() {
		const int size = pq_keys.size();
		// size=6 or 7 => [2]
		for (int root = size/2 - 1; root >= 0; root--) {
			heapify(size, root);
		}
	}
 public:
	PriorityQueue() {}
	PriorityQueue(vector<int>& items) {
		pq_keys = items;
		buildHeap();
	}

	bool empty() { return pq_keys.empty(); }

	int size() { return pq_keys.size(); }

	void push(int item) {
		pq_keys.push_back(item);
		const int size = pq_keys.size();

		// method 1: push the changes up, shift child leftwards
		leftShift(0, size - 1);

		// method 2 is incorrect?
		// method 2: swap([0], [n - 1]), then heapify()
		// const int size = pq_keys.size();
		// swap(pq_keys[0], pq_keys[size - 1]);
		// heapify(size, 0);
	}

	int pop() {
		assert(!pq_keys.empty());
		int topItem = pq_keys[0];
		int lastIdx = pq_keys.size() - 1;
		swap(pq_keys[0], pq_keys[lastIdx]);
		// rm key from container
		pq_keys.pop_back();

		// adjust (max) heap
		heapify(pq_keys.size(), 0);	// root=0 is affected
		return topItem;
	}

	int top() {
		assert(!pq_keys.empty());
		return pq_keys.front();
	}

};

void print(PriorityQueue q) {
	if (q.empty()) return;
	printf("q: ");
	while (!q.empty()) {
		printf("%d ", q.top());
		q.pop();
	}
	printf("\n");
}

void print(const vector<int>& v, string msg="") {
	cout << msg;
	for (int num : v) printf("%d ", num);
	printf("\n");
}

vector<int> getItems(PriorityQueue q) {
	vector<int> items;
	while (!q.empty()) {
		items.push_back(q.top());
		q.pop();
	}
	return items;
}

void test_q_rand(vector<int>& nums) {
	PriorityQueue pq(nums);
	// sort nums in descending order
	sort(nums.begin(), nums.end(), std::greater<int>());
	int maxItem = nums.front();
	assert(pq.top() == maxItem);

	vector<int> items = getItems(pq);
	assert(nums == items);
}

void test_push(vector<int>& nums) {
	PriorityQueue pq;
	for (int num : nums) pq.push(num);

	sort(nums.begin(), nums.end(), std::greater<int>());
	vector<int> items = getItems(pq);
	print(items, "in push test: ");
	assert(nums == items);
}

int main() {
	PriorityQueue pq;
	// insert [1..n]
	int n = 6;
	for (int i = 1; i <= n; i++) pq.push(i);
	print(pq);	// should be 6,5,4,3,2,1
	assert(pq.top() == n);
	vector<int> items;
	for (int i = n; i >= 1; i--) items.push_back(i);

	assert(getItems(pq) == items);

	pq.push(n + 1);
	print(pq);	// should be 7..1
	assert(pq.top() == n + 1);
	assert(pq.size() == n + 1);

	pq.pop();
	print(pq);	// should be 6..1
	assert(pq.top() == n);
	assert(getItems(pq) == items);

	// rm all items
	for (int i = 0; i < n; i++) pq.pop();
	assert(pq.empty());

	// try with rand array
	vector<int> nums = {3,1,5,4,10,9,7,8};
	test_q_rand(nums);

	test_push(nums);

	//   30
	// 20  10
	// 5 6 +7?
	// swap([0],[n-1]), 7 is at root, swap with 20
	// however 30 is gone...
	// thus method 2 is wrong
	vector<int> nums2 = {30,20,10,5,6,7};
	test_push(nums2);

	return 0;
}
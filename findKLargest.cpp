// findKLargest.cpp, LC 215
// find kth largest elment in an array (k >= 1)
// 5/3/2017

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <queue>
using namespace std;
//Given [3,2,1,5,6,4] and k = 2, return 5.

// sort it, O(NlogN), space: O(1), assume heap sort impl
int findKthLargest(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    printf("STL sort: top k-th item: %d\n", nums[nums.size() - k]);
    return nums[nums.size() - k];
}

// [1,2,3], 1 is not among top k=2, rm it
// [2,3,5], 2 is not among top k=2, rm it
// [3,5,6], rm 3
// [4,5,6], rm 4
// finally, take top item
// maintain a min-priority queue, keep size = k, O(Nlogk), space: O(k)
int findKthLargest_pq(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, std::greater<int>> pq;
    for (int num : nums) {
        pq.push(num);
        if (pq.size() > k) pq.pop();
    }
    printf("priority queue: top k-th item: %d\n", pq.top());
    return pq.top();	// get item with max priority
}

int partition(vector<int>& nums, int low, int high) {
    int pivot_id = high;
    int pivot = nums[pivot_id];
    int i = low;
    // mv greater items to the left of pivot
    for (int j = low; j < high; j++) {
        if (nums[j] >= pivot) {
            swap(nums[j], nums[i]);
            i++;
        }
    }
    // finally
    swap(nums[i], nums[pivot_id]);
    return i;
}

// quick sort, T(n) = T(n/2) + O(n), thus time: O(N)
int findKthLargest_qs(vector<int>& nums, int k) {
    int low = 0, high = nums.size() - 1;
    while (true) {
        int pivot_id = partition(nums, low, high);
        if (pivot_id == k - 1) {
            printf("quick sort: top k-th item: %d\n", nums[pivot_id]);
            return nums[pivot_id];
        }
        else if (pivot_id > k - 1) high = pivot_id - 1;
        else low = pivot_id + 1;
    }
}

void heapify(vector<int>& nums, int size, int root) {
    while ((2 * root + 1) < size) {
        int l = 2 * root + 1;	// left child indedx
        int r = 2 * root + 2;	// right child index
        int largest = root;
        if (nums[l] > nums[largest]) largest = l;
        if (nums[r] > nums[largest]) largest = r;
        if (largest != root) {
            swap(nums[largest], nums[root]);
            root = largest;
        }
        else break;
    }
}

// heap sort
int findKthLargest_hs(vector<int>& nums, int k) {
    // make_heap(nums); (STL)
    const int n = nums.size();
    for(int i = n / 2 - 1; i >= 0; i--) {
        heapify(nums, n, i);	// n: heap_size, i: root
    }

    // sort it, but only run k times
    for (int i = 0; i < k; i++) {
        int heap_size = n - 1 - i;
        swap(nums[0], nums[heap_size]);	// curr last
        heapify(nums, heap_size, 0);	// root: 0, only [0] is affected
    }
    printf("heap sort: top k-th item: %d\n", nums[n - k]);
    return nums[n - k];
}

void test(int f(vector<int>&, int), vector<int>& nums, int k, int exp) {
    int res = (*f)(nums, k);
    assert(res == exp);
}

vector<int> createNums() {
    vector<int> nums = {3,2,1,5,6,4};
    return nums;
}

void print(priority_queue<int> pq) {
    while (!pq.empty()) {
        printf("%d, ", pq.top());
        pq.pop();
    }
    printf("\n");
}
void print(const vector<int>& v) {
    for (int num: v) printf("%d, ", num);
    printf("\n");
}

// test push/pop/top of priority queue
void test_pq() {
    // [0,1,2,]
    priority_queue<int> pq;
    int k = 2;
    vector<int> topK;
    int n = 5;
    for (int i = n; i >= 1; i--) {
        pq.push(10 * (n - i));
        if (pq.size() > n - k) {
            topK.push_back(pq.top());
            pq.pop();
        }
    }
    print(pq);
    print(topK);
}

int main() {
    vector<int> nums = createNums();
    int k = 2;
    int exp = 5;

    test(findKthLargest, nums, k, exp);	// nums sorted

    nums = createNums();
    test(findKthLargest_pq, nums, k, exp);

    nums = createNums();
    test(findKthLargest3, nums, k, exp);

    nums = createNums();
    test(findKthLargest4, nums, k, exp);

    // test_pq();

    return 0;
}

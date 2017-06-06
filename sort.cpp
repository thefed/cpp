// impl some sort algorithms
// insertion sort, 4/3/2017
// quick sort, merge sort, selection sort 4/21/2017

// heap sort, 5/1/2017

/* what is stable sort?
   - after sort, if two elements are equal, then their order should be the same as before
   - (4, "first"), (2, ""), (3, ""), (4, "second")
   - quick sort's partition utility is not stable!
   - how to fix? Add a second key (indicating the original order, say seq # or index)
   */

#include <iostream>
#include <algorithm> // swap, is_sorted
#include <vector>
#include <cassert>
using namespace std;
void print(const vector<int> &v) {
    for (auto num : v) printf("%d, ", num);
    printf("\n");
}

// time O(N^2), space O(1), manipulate array in place
// worse case: input is sorted in descending order
// O(N^2) swaps, O(N^2) comparisons
void insertSort(vector<int> &vec) {
    print(vec);
    for (int i = 1; i < vec.size(); i++) {
        // pick the i-th element, 
        int valueToInsert = vec[i];
        int pos = i;    // assumed inserted position

        // find its expected inserted position in the sorted subarray 
        // move elements forward if there are elements greater than it
        while (pos > 0 && vec[pos - 1] > valueToInsert) {
            // move previous greater values forward
            vec[pos] = vec[pos - 1];
            pos--;  
        }
        // place it at the found position
        vec[pos] = valueToInsert;
        printf("%d's inserted pos: %d\n", valueToInsert, pos);
        print(vec);
        printf("\n");
    }
}

// take rightmost element as pivot (or leftmost/median/random)
// move the elements (< pivot) to the left of it, others to the right
// place pivot element at its correct position in the sorted array
int partition(vector<int> &vec, int low, int high) {
    // {33, 14, 27, 10, 35, 19, 42, 24}, pivot = 24
    int pivot = vec[high];
    int i = low;	// index/counter of the smaller elements

    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivot) {
            swap(vec[i], vec[j]);	// move curr to its correct position
            i++;
        }
        // otherwise, skip it
    }
    // example: 14,10,19, 33,27,35,42,   24
    // move pivot to the end of its smaller elements [i]
    swap(vec[i], vec[high]);            // if vec[i] == vec[i+1], swapped to back, then it is unstable
    return i;	// move 24 to vec[3]
}

// sort elements from index [low, high] of array vec (divide and conquer)
// worse case: O(N^2), choose rightmost as pivot, input almost sorted
// example: 1 2 3 4 5 6, pivots chosen: 6/5/4/3/2/1, N rounds in all, not log(N)

// average: O(N logN)
void quickSort(vector<int> &vec, int low, int high) {
    if (low < high) {
        // divide: find pivot index, swap elements, does the main work
        int pivot_id = partition(vec, low, high);
        printf("sort vec[%d, %d], pivot: [%d], %d\n", low, high, pivot_id, vec[pivot_id]);
        print(vec);
        printf("\n");
        // conquer, sort elements before and after pivot respectively
        quickSort(vec, low, pivot_id - 1);
        quickSort(vec, pivot_id + 1, high);
    }
}

// merge two sorted subarrays
void merge(vector<int> &vec, int low, int mid, int high) {
    // [low, mid], [mid + 1, high]
    // high=3, mid=1, [0,1] [2,3]
    // high=4, mid=2, [0,2] [3,4]
    // example: 14, 33,// 27, 10

    // copy two subarrays of vec to nums
    vector<int> nums(vec.begin() + low, vec.begin() + high + 1);

    int len1 = mid - low + 1, len2 = high - low + 1;
    int i = 0, j = len1;	// indices for two pointers
    int id = low;	// starting index of output

    // place smaller element to output vec one by one
    while (i < len1 && j < len2) {
        vec[id++] = (nums[i] <= nums[j]) ? nums[i++] : nums[j++];
    }
    // copy the rest elements to vec
    while (i < len1) vec[id++] = nums[i++];
    while (j < len2) vec[id++] = nums[j++];
}

// time: O(NlogN), space: O(N) for array, O(logN) for stack space
void mergeSort(vector<int> &vec, int low, int high) {
    if (low < high) {
        printf("sort vec[%d, %d]\n", low, high);
        int mid = low + (high - low) / 2;
        mergeSort(vec, low, mid);
        mergeSort(vec, mid + 1, high);

        // merge the two sorted subarrays, does the main work
        merge(vec, low, mid, high);
        printf("merge vec[%d, %d]\n", low, high);
        print(vec);
    }
}

// O(N^2): worse case: input is sorted in descending order
// O(N^2) comparisions, only O(N) swaps
void selectionSort(vector<int> &vec) {
    for (int i = 0; i < vec.size() - 1; i++) {
        // always select the min item from the rest unsorted subarray
        int min_idx = i;		// assumed to be i
        for (int j = i + 1; j < vec.size(); j++) {
            if (vec[j] < vec[min_idx]) {
                min_idx = j;	// update min_idx;
            }
        }
        // swap min item with current one
        swap(vec[i], vec[min_idx]);
    }
}

// to heapify a subtree rooted at node [root], which
// is an index in vec, 
// end is the max index + 1 of vec
// time: O(logN)
void heapify(vector<int>& vec, int end, int root) {
    int largest = root;    // initialize largest as root (i)
    int l = 2*root + 1;
    int r = 2*root + 2;    // left/right child
    // in a max heap, root should > left/right
    if (l < end && vec[l] > vec[largest]) largest = l;
    if (r < end && vec[r] > vec[largest]) largest = r;
    if (largest != root) {
        swap(vec[largest], vec[root]);
        root = largest;
        // heapify the affected subtree recursively
        heapify(vec, end, root);
    }
}

// iterative version: heapify
void heapify2(vector<int>& vec, int end, int root) {
    while ((2*root + 1) < end) {
        int l = 2*root + 1;
        int r = 2*root + 2;
        int largest = root;
        // no need to check l < end
        if (vec[l] > vec[largest]) largest = l;
        if (r < end && vec[r] > vec[largest]) largest = r;
        if (largest != root) {
            // swap the root(smaller than child) to the subtree
            swap(vec[largest], vec[root]);
            root = largest;
        }
        // otherwise, no need to touch current root, return/break
        else break; // largest == root, no subtree is affected
    }
}

void heapSort(vector<int>& vec) {
    // build heap
    const int n = vec.size();
    // heapify from bottom
    // why from "n/2 - 1"? if n=2^k-1 or 2^k-2, its child=(n-1-1)/2
    // n=6 or 7, [5][6]'s child is [2], if n=4 or 5, check [3][4]'s child [1]
    //
    // time: sift down method to build max heap: O(N), siftDown
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(vec, n, i);
    }

    // take item (max) from root, mv to tail, O(logN) * O(N), siftUp
    for (int i = n - 1; i >= 0; i--) {
        swap(vec[0], vec[i]);
        // heapify(vec, i, 0); // end=i,root=0, recursive way

        heapify2(vec, i, 0); // end=i,root=0, iterative way
    }
}

// pass sort function pointers as parameters
void test(void sortFunc(vector<int>&, int, int), vector<int> vec, string sortName="") {
    cout << sortName << endl;
    (*sortFunc)(vec, 0, vec.size() - 1);
    assert(is_sorted(vec.begin(), vec.end()));
}
void test(void sortFunc(vector<int>&), vector<int> vec) {
    (*sortFunc)(vec);
    assert(is_sorted(vec.begin(), vec.end()));
}
int main() {
    // vector<int> vec = {33, 14, 27, 10, 35, 19, 42, 24};
    vector<int> vec = {4,10,3,5,1,7,6};
/*      
            4
        10      3
       5  1    7 6
*/

    printf("Original array: ");
    print(vec);
    /*

    // printf("Insertion sort: \n");
    // insertSort(vec);

    printf("Quick sort: \n");
    //quickSort(vec, 0, vec.size() - 1);
    test(quickSort, vec);
    test(mergeSort, vec, "Merge sort");

    // printf("Merge sort: \n");
    // mergeSort(vec, 0, vec.size() - 1);

    test(selectionSort, vec);
    test(insertSort, vec);

    printf("Insertion sort: \n");
    selectionSort(vec);
    */

    printf("Heap sort: \n");
    heapSort(vec);

    // verify vec is sorted
    print(vec);
    assert(is_sorted(vec.begin(), vec.end()));
}

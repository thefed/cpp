// akuna 
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
using namespace std;
void print(vector<float>& v, string msg="") {
	cout << msg;
	for (float f: v) printf("%f ", f);
	printf("\n");
}
vector<int> nearSum(vector<int>& nums, int n) {
	int sum = 0;
	vector<int> res(2);
	size_t size = nums.size();
	int min_diff = INT_MAX;
	int diff;
	int prev_diff;
	for (int i = 0; i < size; i++) {
		sum = nums[i]; // reset sum to nums[i]
		diff = abs(sum - n);
		if (diff == 0) {
			res = {i,i};
			return res;
		}
		else if (diff < min_diff) {
			min_diff = diff;
			res = {i,i};
		}
		prev_diff = diff;	// init prev diff

		printf("i=%d, sum=%d\n", i, sum);
		// add from [i+1..j]
		for (int j = i + 1; j < size; j++) {
			sum += nums[j];
			diff = abs(n - sum);

			printf("j=%d, sum=%d\n", j, sum);

			if (diff == 0) {
				res = {i, j};
				return res;
			}
			else if (diff < min_diff) {
				min_diff = diff;
				res = {i, j};
				printf("min_diff %d\n", min_diff);
			}
			// no better solution from [i..j]
			else if (diff > prev_diff) {
				printf("i: %d, j=%d, break\n", i,j);
				break;
			}
			prev_diff = diff;
		}
	}
	return res;
}

void test_nearSum() {
	vector<int> nums = {7,6,3,5,4,2};
	int n = 14;
	vector<int> exp = {1,3};
	vector<int> res = nearSum(nums, n);
	printf("[%d,%d]\n", res[0], res[1]);
	assert(res == exp);

	n = 11;
	res = nearSum(nums, n);
	printf("[%d,%d]\n", res[0], res[1]);
	exp = {3,5};
	assert(res == exp);
}

int findLast(vector<int>& nums, int k) {
	if (nums.size() == 1) return 0;//nums[0];

	int low = 0, high = nums.size() - 1;
	int mid;
	while (low + 1 < high) {
		mid = low + (high - low) / 2;
		if (nums[mid] > k) {
			high = mid - 1;
		}
		else {	// <=
			low = mid;
		}
	}
	int last = (nums[high] <= k ? high : low);
	return last;
}

// find median of the subarray (taken from sorted array, where values <= k)
double findMedian(vector<int>& nums, int k) {
	// find last element <= k in a sorted array
	int last = findLast(nums, k);
	// find median [0..last] 
	int mid = (last + 1) / 2;
	if ((last + 1) % 2 == 0) {
		return ((double)nums[mid] + nums[mid - 1]) / 2.0;
	}
	else return double(nums[mid]);
}

void test_findLast() {
	vector<int> nums = {1,2,3,4,5,5,6};
	int k = 1;
	int res = findLast(nums, k);
	printf("res: %d\n", res);
	assert(res == 0);

	k = 2;
	res = findLast(nums, k);
	printf("res: %d\n", res);
	assert(res == 1);

	k = 3;
	res = findLast(nums, k);
	printf("res: %d\n", res);
	assert(res == 2);

	assert(findLast(nums, 4) == 3);

	assert(findLast(nums, 5) == 5);

	assert(findLast(nums, 6) == 6);

	assert(findLast(nums, 10) == 6);

	assert(findLast(nums, 0) == 0);
}	

void test_findMedian() {
	vector<int> nums = {1,2,3,4,5,5,6};
	int k = 4;
	double res = findMedian(nums, k);
	printf("res: %f\n", res);
	assert(res == 2.5);

	k = 6;
	res = findMedian(nums, k);
	printf("res: %f\n", res);
	assert(res == 4.0);

	k = 5;
	res = findMedian(nums, k);
	printf("res: %f\n", res);
	assert(res == 3.5);

	assert(findMedian(nums, 1) == 1.0);
	assert(findMedian(nums, 2) == 1.5);
	assert(findMedian(nums, 3) == 2.0);
}

bool isConverged(vector<float>& m1, vector<float>& m2, float delta=1e-7) {
	float max_diff = abs(m1[0] - m2[0]);
	for (int i = 1; i < m1.size(); i++) {
		float diff = abs(m1[i] - m2[i]);
		if (diff > max_diff) max_diff = diff;
	}
	return max_diff < delta;
}

// matrix m1: 1xn size, m2: nxn size
// return result matrix: m1 * m2 ^ n, until convergence
// floats output are rounded to 4 decimal places
vector<float> converge(vector<float>& m1, vector<vector<float>>& m2) {
	int n = m1.size();
	vector<float> res(n, 0.0);
	for (int i = 0; i < n; i++) {		// n cols
		for (int j = 0; j < n; j++) {
			res[i] += m1[j] * m2[j][i];
		}
	}
	print(res);
	vector<float> exp = {0.38, 0.62};
	// assert(res == exp);

	// int cnt = 0;
	while (!isConverged(res, m1)) {//} && cnt < 4) {
		m1 = res;
		// res.resize(n, 0.0);
		fill(res.begin(), res.end(), 0.0);
		// print(res, "res.resize:");
		// print(m1, "m1:");
		for (int i = 0; i < n; i++) {		// n cols
			for (int j = 0; j < n; j++) {
				res[i] += m1[j] * m2[j][i];
			}
		}
		print(res, "res:");
		assert(res[0] < 1);
		assert(res[1] < 1);
		// cnt++;
	}
	// round result to 4 points decimal
	for (int i = 0; i < n; i++) res[i] = round(res[i] * 1e4) / 1e4;
	return res;
}
void test_converge() {
	vector<float> m1 = {0.4,0.6};
	vector<vector<float>> m2 = {
		{0.8, 0.2}, {0.1, 0.9}
	};
	vector<float> res = converge(m1, m2);
	vector<float> exp = {0.3333, 0.6667};
	assert(res == exp);
}

int main() {
	// test_nearSum();
	// test_findLast();	

	// test_findMedian();

	test_converge();

	return 0;	
}
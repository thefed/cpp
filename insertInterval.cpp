//insertInterval.cpp
// LC 57
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

/*
Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
*/

// insert interval to 
vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
    vector<Interval> res;
    int s = newInterval.start, e = newInterval.end;
    // find the last inter.end < start
    

    // process the middle, choose min(s, interval.start), choose max(e, interval.end)
    
    // find the 1st inter.start > e
    
    // or one pass
    int n = intervals.size();
    int i = 0;
    while (i < n && intervals[i].end < s) res.push_back(intervals[i++]);
    
    int min_s = s, max_e = e;
    while (i < n && intervals[i].start <= e) {
        min_s = min(intervals[i].start, min_s);
        max_e = max(intervals[i].end, max_e);
        printf("min_s = %d, max_e = %d\n", min_s, max_e);
        i++;
    }
    if (i <= n) {
        res.push_back(Interval(min_s, max_e));
    }
    
    // int j = n - 1;
    // while (j >= 0 && intervals[j].start > end) j--;
    
    if (i < n) {
        res.insert(res.end(), intervals.begin() + i, intervals.end());
    }
    
    return res;
}
void print(const vector<Interval> &v) {
	for (Interval it : v) printf("[%d, %d],\n", it.start, it.end);
	printf("\n");
}

// overload '==' to compare intervals
bool operator==(const Interval &i1, const Interval &i2) {
  	return i1.start == i2.start && i1.end == i2.end;
}

int main() {
	vector<Interval> intervals = {{1,5}, {6, 8}};
	Interval interval = Interval(5,6);
	vector<Interval> res = insert(intervals, interval);
	print(res);
	// assert(res == (vector<Interval> {Interval(1,8)}));
	assert(res == (vector<Interval> {{1,8}}));
	return 0;
}
// test usage of "auto" keyword with "&", map, sort()
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

void print(const std::vector<int> &v) {
    for (auto it: v) printf("%d ", it);
    printf("\n");
}

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e): start(s), end(e) {}
};
int main() {
    map<int, char> dict {{1, 'A'}, {2, 'B'}, {3, 'C'}};
    // for (auto &it : dict) cout << it.first << " " << it.second << endl; 

    multimap<int, char> mm {{2, 'B'}, {3, 'C'}, {3, 'D'}, {3, 'E'}, {1, 'A'}};
    for (auto &it: mm) cout << it.first << " " << it.second << endl; 

    cout << endl;
    auto range = mm.equal_range(3);
    for (auto it = range.first; it != range.second; it++)
        cout << it->first << " " << it->second << endl; 

    // custom comp function when calling sort()
    vector<int> v = {5, 7, 4, 3, 1, 2};
    sort(v.begin(), v.end());
    print(v);

    sort(v.begin(), v.end(), std::greater<int>());
    print(v);

    struct
    {
        bool operator() (int a, int b) {
            return a < b;
        }
    } comp;

    sort(v.begin(), v.end(), comp);
    print(v);

    vector<Interval> vec = {Interval(3, 1), Interval(2, 4), Interval(1, 5)};
    struct 
    {
        bool operator() (const Interval &a, const Interval &b) {
            return a.start < b.start;
        }
    } compi;
    // auto compi = [](const Interval &a, const Interval &b) {return a.start < b.start; };
    sort(vec.begin(), vec.end(), compi);
    for (auto &it : vec) cout << it.start << ", ";
    cout << endl;
    return 0;
}

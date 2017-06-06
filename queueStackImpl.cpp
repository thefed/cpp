// implement queue with stack, C++, LC 232
#include<iostream>
#include<stack>
#include<assert.h>
using namespace std;
class Queue {
    stack<int> items;
    private:
    stack<int> reverse(stack<int> src) {
        stack<int> dest;
        while (!src.empty()) {
            dest.push(src.top());
            src.pop();
        }
        return dest;
    }

    public:
    void push(int x) {
        // + 1 => [1]
        // + 2 => [2,1]
        // + 3 => [3,2,1]
        items = reverse(items);
        items.push(x);
        items = reverse(items);
    }
    void pop() {
        assert(!items.empty());
        items.pop();
        /*
        stack<int> reversedData = reverse(items);
        reversedData.pop();
        items = reverse(reversedData);
        */
    }
    int peek() {
        assert(!items.empty());     // invalid memory access => seg fault
        /*
        stack<int> reversedData = reverse(items);
        return reversedData.top();
        */
        return items.top();
    }
    bool empty(void) { return items.empty(); }
};
int main() {
    Queue q;
    int n = 5;  // push 1..5
    for (int i = 1; i <= n; i++) q.push(i);
    assert(q.peek() == 1);  // get first element
    q.pop();
    assert(q.peek() == 2);
    return 0;
}

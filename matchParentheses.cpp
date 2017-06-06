#include<iostream>
#include<string>
#include<stack>
#include<assert.h>
using namespace std;
bool isValidParentheses(string s) {
    stack<char> st;
    for (int i = 0; i < s.size(); i++) {
        // if curr char is left parenthesis, push to stack
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            st.push(s[i]);
        }
        // if curr char is right parenthesis and matches stack top, pop it
        else if ((s[i] == ')' && !st.empty() && st.top() == '(') 
                || (s[i] == ']' && !st.empty() && st.top() == '[') 
                || (s[i] == '}' && !st.empty() && st.top() == '{')) {
            st.pop();
        }
        // otherwise return false
        else {
            return false; 
        }
    }
    return st.empty();
}
int main() {
    string s1 = "{([])}()";
    assert(isValidParentheses(s1) == true);
    string s2 = "{([]]}}()";
    assert(isValidParentheses(s2) == false);
    return 0;
}

// G, phone
// split string by spaces, if string contains double quotes, treat the content inside as one word
// "this is an \"example string\" test"
#include <iostream>
#include <string> 
#include <vector>
#include <cassert>
using namespace std;
vector<string> split(string &s) {
    vector<string> res;
    if (s.empty()) return res;

    bool isQuote = false;
    int start = 0;
    int i;
    for (i = 0; i < s.size(); i++) {
        if (!isQuote) {
            if (s[i] == '\"') {
                start = i + 1;  // start of quotes
                isQuote = true;
            } 
            else if (s[i] == ' ' && i - start > 0) {
                res.push_back(s.substr(start, i - start));
                start = i + 1;
            }
            else if (s[i] == ' ') start = i + 1;    // skip it
        }
        else {
            if (s[i] == '\"') { // end of quotes
                res.push_back(s.substr(start, i - start));
                isQuote = false;
                start = i + 1;
            }
        }
    }
    // last word
    if (i > start) res.push_back(s.substr(start, i - start));

    return res;
}
int main() {
    string s1 = "this is an example string.";
    vector<string> exp = {"this", "is", "an", "example", "string."};
    vector<string> res = split(s1);
    assert(res == exp);

    s1 = "this line is \"an example\" string.";
    exp = {"this", "line", "is", "an example", "string."};
    res = split(s1);
    assert(res == exp);

    s1 = "test string \"last\"";
    exp = {"test", "string", "last"};
    res = split(s1);
    assert(res == exp);
}

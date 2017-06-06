#include <iostream>
#include <cassert>
#include <string>
using namespace std;

// impl strcpy
char* strcpy(char *dest, const char *src) {
    printf("Start of strcpy: \n");
    printf("&dest: %p, &src: %p\n", &dest, &src);
    printf("dest: %p, src: %p\n", dest, src);
    // one line! place parentheses around the assignment to
    // silence this warning
    char *p = dest;
    while ((*dest++ = *src++));
    printf("End of strcpy: \ndest: %p, src: %p\n\n", dest, src);
    return p;	// return the destination string
}
void test_strcpy() {
    char s1[] = "Sample string";
    char s2[40];
    // char s3[40];
    printf("Before strcpy\ndest: %p, src: %p\n", s2, s1);
    printf("&dest: %p, &src: %p\n\n", &s2, &s1);
    char *s4 = strcpy(s2, s1);
    printf("After strcpy: \ndest: %p, src: %p\n\n", s2, s1);

    printf("s4: %s\n", s4);

    // strcpy(s3, "copy success");
    // printf("s1: %s\ns2: %s\ns3: %s\n", s1, s2, s3);
}

// impl strstr
const char * strstr2(const char *src, const char * pattern) {
    while (*src) {
        const char *s = src;		// start of string
        const char *p = pattern;
        while (*src && *p == *src) {
            p++;
            src++;
        }
        if (*p == '\0') return s;
        src = s + 1;
    }
    return NULL;	// not found
}

void test_strstr() {
    char str[] = "This is a simple string";
    const char *pch = strstr2(str, "string");
    assert(pch);
    printf("found: %s\n", pch);
    // assert(strcmp(pch, "simple string") == 0);
}

// check usage of substr
void test_substr() {
    string s = "abcdefg";
    cout << s.substr(1) << endl;	// cp till end, "bcdefg"
    cout << s.substr(1, 2) << endl;	// cp count=2 chars, "bc"
}

int main() {
    test_substr();

    test_strcpy();

    test_strstr();
    return 0;
}

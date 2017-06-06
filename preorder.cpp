// 5/3/2017, simplify it
#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>
using namespace std;
struct TreeNode{
    int val;
    TreeNode *left, *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};
// recursive method
void preorderHelper(TreeNode *root, vector<int>& values) {
    if (root == NULL) return;
    values.push_back(root->val);
    preorderHelper(root->left, values);    
    preorderHelper(root->right, values);    
}
vector<int> preorderRecursive(TreeNode *root) {
    vector<int> values; // returned values of all nodes
    preorderHelper(root, values);
    return values;
}

// divide & conquer method
vector<int> preorderDC(TreeNode *root) {
    vector<int> res;
    if (root == NULL) return res;
    vector<int> leftRes = preorderDC(root->left);
    vector<int> rightRes = preorderDC(root->right);
    // this operation is expensive!!
    res.push_back(root->val);
    res.insert(res.end(), leftRes.begin(), leftRes.end());
    res.insert(res.end(), rightRes.begin(), rightRes.end());
    return res;
}

// iterative method, use stack
vector<int> preorder(TreeNode *root) {
    vector<int> res;
    if (root == NULL) return res;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode *curr = st.top();
        res.push_back(curr->val);
        st.pop();
        // push right child, then left child
        // thus left one is processed first
        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);
    }
    return res;
}
void deleteTree(TreeNode *root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
void print(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); i++) printf("%d ", vec[i]);
    printf("\n");
}
int main() {
    //      1
    //     / \
    //    2   3
    //   / \ / \
    //  4  5 6 
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);

    vector<int> res = preorder(root);
    vector<int> expected = {1,2,4,5,3,6};
    print(res);
    assert(res == expected);

    res = preorderDC(root);
    assert(res == expected);
    
    res = preorderRecursive(root);
    assert(res == expected);
    deleteTree(root);
    return 0;
}

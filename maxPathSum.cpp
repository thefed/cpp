// hard: max path sum
#include<iostream>
#include<climits>
#include<algorithm>
#include<assert.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
struct ResultT {
    int singlePath; // path length from root to either left or right tree, may contain root node only
    int maxPath;    // max path length, 3 cases, the left subtree or right subtree, or the path spaning from left tree, over root, to right subtree
    ResultT(int s, int m) : singlePath(s), maxPath(m) {}
};
ResultT* helper(TreeNode *root) {
    if (!root) return new ResultT(0, INT_MIN);
    // divide
    ResultT *leftRes = helper(root->left);
    ResultT *rightRes = helper(root->right);
    // conquer
    int singlePath = max(leftRes->singlePath, rightRes->singlePath) + root->val;
    singlePath = max(singlePath, 0);    // in case singlePath < 0, set it to 0
    int maxPath = max(leftRes->maxPath, rightRes->maxPath);
    maxPath = max(maxPath, leftRes->singlePath + rightRes->singlePath + root->val);
    return new ResultT(singlePath, maxPath);
}
// max path may start/end with any tree node
int maxPathSum(TreeNode *root) {
    ResultT *resultT = helper(root);
    return resultT->maxPath;
}
int main() {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    int maxPath = maxPathSum(root);
    assert(maxPath == 6);
    return 0;
}

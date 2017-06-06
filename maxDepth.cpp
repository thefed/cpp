// get max depth of a binary tree
#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
#include<assert.h>
using namespace std;
struct TreeNode {
    int val; 
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//      1
//     / \
//    2   3
//   / \
//  4   5
//     /
//    6
int maxDepth(TreeNode *root) {
    if (!root) return 0;
    // iterative DFS
    stack<TreeNode*> st;
    stack<int> depths;  // store depth at different levels
    st.push(root);
    depths.push(1);
    int max_depth = 0;
    while (!st.empty()) {
        TreeNode *curr = st.top();
        st.pop();
        int currDepth = depths.top();
        depths.pop();
        // update max_depth
        max_depth = max(max_depth, currDepth);
        if (curr->left) {
            st.push(curr->left);
            depths.push(currDepth + 1);
        }
        if (curr->right) {
            st.push(curr->right);
            depths.push(currDepth + 1);
        }
    }
    return max_depth;

    // recursive solution
    // return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// level order, BFS, queue
int maxDepth_bfs(TreeNode *root) {
    if (!root) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int height = 0;
    while (!q.empty()) {
        height++;
        // scan each node in curr level, push their children to q
        const int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode *curr = q.front();
            q.pop();
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    return height;
}

// divide & conquer: get left subtree's height, then right substree's, take greater one
int maxDepth_dc(TreeNode *root) {
    if (!root) return 0;
    int leftDepth = maxDepth_dc(root->left);
    int rightDepth = maxDepth_dc(root->right);
    return 1 + max(leftDepth, rightDepth);
}

// preorder traversal from curr depth
void traverse(TreeNode *root, int currDepth, int &max_depth) {
    if (!root) return;
    if (currDepth > max_depth) max_depth = currDepth;
    traverse(root->left, currDepth + 1, max_depth);
    traverse(root->right, currDepth + 1, max_depth);
}

int maxDepth_recursive(TreeNode *root) {
    int max_depth = 0;
    int currDepth = 0;
    traverse(root, currDepth, max_depth);
    return max_depth;
}

void deleteTree(TreeNode *root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    assert(maxDepth(NULL) == 0);    // empty tree's depth should be 0

    TreeNode *root = new TreeNode(1);
    assert(maxDepth(root) == 1);    // single root node, height = 1

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    assert(maxDepth(root) == 3);    // level 3

    root->left->right->left = new TreeNode(6);
    int max_depth = maxDepth(root);
    assert(max_depth == 4);

    assert(maxDepth_recursive(root) == 4);

    assert(maxDepth_dc(root) == 4);

    assert(maxDepth_bfs(root) == 4);

    deleteTree(root);
    return 0;
}

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
void dfs(TreeNode *root, vector<int> &level, int currLevel, int maxLevel) {
    if (root == NULL || currLevel > maxLevel) return;
    if (currLevel == maxLevel) {
        level.push_back(root->val);
        return;
    }
    // currLevel < maxLevel
    dfs(root->left, level, currLevel + 1, maxLevel);
    dfs(root->right, level, currLevel + 1, maxLevel);
}
vector<int> levelOrderWithDFS(TreeNode *root) {
    vector<int> res;
    if (!root) return res;
    int maxLevel = 0;
    while (true) {
        vector<int> level;
        dfs(root, level, 0, maxLevel);
        // now no nodes in curr level, reaching leaf nodes
        // should exit
        if (level.empty()) {
            break;
        }
        res.insert(res.end(), level.begin(), level.end());
        maxLevel++;
    }
    return res;
}
vector<int> levelOrder(TreeNode *root) {
    vector<int> res;
    if (!root) return res;
    // BFS, queue
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        // scan each node in curr level, push their children to q
        const int Q_SIZE = q.size();
        for (int i = 0; i < Q_SIZE; i++) {
            TreeNode *curr = q.front();
            q.pop();
            res.push_back(curr->val);
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    return res;
    // recursive solution
    // return 1 + max(maxDepth(root->left), maxDepth(root->right));
}
int sumlevelOrder(TreeNode *root) {
    int sum = 0;
    if (!root) return sum;
    // BFS, queue
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        // scan each node in curr level, push their children to q
        const int Q_SIZE = q.size();
        for (int i = 0; i < Q_SIZE; i++) {
            TreeNode *curr = q.front();
            q.pop();
            //res.push_back(curr->val);
            sum += curr->val;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    return sum;
    // recursive solution
    // return 1 + max(maxDepth(root->left), maxDepth(root->right));
}
    
void deleteTree(TreeNode *root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
bool cmpVec(const vector<int> &v1, const vector<int> &v2) {
    if (v1.size() != v2.size()) return false;
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) return false;
    }
    return true;
}
int main() {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->left = new TreeNode(6);
    int array[6] = {1, 2, 3, 4, 5, 6};
    vector<int> expected(array, array + sizeof(array) / sizeof(int));
    //vector<int> res = levelOrder(root);
    //assert(cmpVec(res, expected) == true);

    vector<int> res2 = levelOrderWithDFS(root);
    assert(cmpVec(res2, expected) == true);

    assert(sumlevelOrder(root) == 21);

    deleteTree(root);
    cout << "success.\n";
    return 0;
}

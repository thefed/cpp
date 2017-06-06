// isBST, LC 98, 4/3/2017

#include<iostream>
#include<stack>
#include<cassert>
#include<queue>
using namespace std;
// define a TreeNode
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool validate(TreeNode *root, TreeNode *prev) {
    if (!root) return true;
    if (!validate(root->left, prev)) return false;
    if (prev && prev->val >= root->val) return false;
    prev = root;
    return validate(root->right, prev);
}

// inorder traversal should return a sorted array! (ascending)
bool isBST(TreeNode *root) {
    // recursive solution, inorder traversal
    //TreeNode *prev = NULL;
    //return validate(root, prev);

    // iterative solution, inorder traversal
    stack<TreeNode *> st;
    TreeNode *pre = NULL;
    while (root || !st.empty()) {
        while (root) {
            st.push(root);
            root = root->left;
        }
        // take the top element
        root = st.top();
        st.pop();
        if (pre) cout << "pre: " << pre->val;
        cout << " root:" << root->val << endl;
        if (pre && pre->val >= root->val) return false;
        pre = root;
        root = root->right;
    }
    return true;
}

void deleteTree(TreeNode *root) {
    if (!root) return;
    // postorder
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void printTree(TreeNode *root) {
    // level order traversal 
    if (!root) return;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode *curr = q.front();
            q.pop();
            if (!curr) {
                cout << "N "; 
            }
            else {
                cout << curr->val << " ";
                q.push(curr->left); 
                q.push(curr->right); 
            }
        }
        cout << endl;
    }
}

int main() {
    assert(isBST(NULL));
    // create a tree
    //      4
    //    2   5
    //   1 3 N N
    TreeNode *root = new TreeNode(4);
    assert(isBST(root));

    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    printTree(root);
    
    assert(isBST(root));
    deleteTree(root);
    return 0;
}

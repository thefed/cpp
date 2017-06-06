// tree practice
// 5/3/2017

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void deleteTree(TreeNode *root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void printTree(TreeNode *root) {
    if (!root) return;
    printf("%d ", root->val);
    printTree(root->left);
    printTree(root->right);
}
void print(TreeNode *root, string msg="") {
    cout << msg;
    printTree(root);	// inorder traversal
    printf("\n");
}

int getHeight(TreeNode *root) {
    if (!root) return 0;
    int leftHeight = getHeight(root->left);
    if (leftHeight == -1) return -1;

    int rightHeight = getHeight(root->right);
    if (rightHeight == -1) return -1;
    if (abs(leftHeight - rightHeight) > 1) return -1;

    // return the normal height
    return 1 + max(leftHeight, rightHeight);
}
// check if a tree is height-balanced
bool isBalanced(TreeNode *root) {
    return getHeight(root) != -1;
}

// inorder traversal of tree, return an array of items
vector<int> getItems(TreeNode *root) {
    vector<int> items;
    stack<TreeNode *> st;
    while (root || !st.empty()) {
        if (root) {
            st.push(root);
            root = root->left;
        }
        else {
            root = st.top();
            st.pop();
            items.push_back(root->val);	// access left, then root, then right
            root = root->right;
        }
    }
    return items;
}

vector<int> getItems_pre(TreeNode *root) {
    vector<int> items;
    if (!root) return items;
    stack<TreeNode *> st;
    st.push(root);
    while (!st.empty()) {
        root = st.top();
        st.pop();
        items.push_back(root->val);

        if (root->right) st.push(root->right);	// visit right lastly
        if (root->left) st.push(root->left);
    }
    return items;
}

vector<int> getItems_post(TreeNode *root) {
    vector<int> items;
    if (!root) return items;
    stack<TreeNode *> st;
    while (!root || !st.empty()) {
        if (root) {
            st.push(root);	// visit root, then its right child
            items.insert(items.begin(), root->val);
            root = root->right;
        }	
        else {
            TreeNode *node = st.top();
            st.pop();	// as parent & right are visited
            root = node->left;
        }
    }
    return items;
}

TreeNode* insert(TreeNode *root, int x) {
    if (!root) return new TreeNode(x);
    if (x < root->val) {
        if (root->left) insert(root->left, x);
        else root->left = new TreeNode(x);
    }
    else {
        if (root->right) insert(root->right, x);
        else root->right = new TreeNode(x);
    }
    return root;
}

// create binary search tree from array
TreeNode* createBST(const vector<int>& items) {
    TreeNode *root = NULL;
    for (int i : items) root = insert(root, i);
    return root;
}

// create AVL tree by a given range
TreeNode* createAVL(const vector<int>& items, int start, int end) {
    if (start > end) return NULL;
    if (start == end) return new TreeNode(items[start]);
    int mid = start + (end - start + 1) / 2;
    TreeNode *root = new TreeNode(items[mid]);
    root->left = createAVL(items, start, mid - 1);
    root->right = createAVL(items, mid + 1, end);
    return root;
}

// create balanced BST from sorted array 
TreeNode* createBalancedBST(const vector<int>& items) {
    return createAVL(items, 0, items.size() - 1);
}
void test_height() {
    TreeNode *root = new TreeNode(1);
    assert(isBalanced(root)); 

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    assert(isBalanced(root));

    deleteTree(root);
}

void test_AVL() {
    vector<int> items = {1,2,3,5,4};
    /* 1
     *  \
     *  2
     *  \
     *  3
     *   \
     *   5
     *   /
     *   4
     */
    TreeNode *root = createBST(items);
    print(root);

    vector<int> items_exp = {1,2,3,4,5};
    assert(getItems(root) == items_exp);
    deleteTree(root);

    root = createBalancedBST(items_exp);
    print(root);
    assert(getHeight(root) == 3);
    deleteTree(root);

    vector<int> items2 = {1,2,3,4,5,6,7,8};
    root = createBalancedBST(items2);
    print(root);
    assert(getHeight(root) == 4);
    deleteTree(root);
}

void test_traversal() {
    vector<int> items = {1,2,3,4,5,6};
    /*   4
     * 2   6
     *1 3 5 N */
    TreeNode *root = createBalancedBST(items);	
    // inorder
    vector<int> inorder_items = getItems(root);
    assert(inorder_items == items);

    vector<int> preorder_items = getItems_pre(root);
    assert(preorder_items == (vector<int> {4,2,1,3,6,5}));

    vector<int> postorder_items = getItems_pre(root);
    assert(postorder_items == (vector<int> {1,3,2,5,6,4}));
}

int main() {
    //test_height();

    test_AVL();
}

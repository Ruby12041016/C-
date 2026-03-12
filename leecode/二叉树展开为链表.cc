#include <stack>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
   public:
    void order_1(TreeNode* root, vector<int>& val) {
        if (!root) {
            return;
        }
        val.push_back(root->val);
        order_1(root->left, val);
        order_1(root->right, val);
    }
    TreeNode* add(vector<int> val) {
        if (val.empty())
            return nullptr;
        TreeNode* new_tree_root = new TreeNode(val[0]);
        TreeNode* temp = new_tree_root;
        for (int i = 1; i < val.size(); i++) {
            temp->left = NULL;
            temp->right = new TreeNode(val[i]);
            temp = temp->right;
        }
        return new_tree_root;
    }
    void flatten(TreeNode* root) {
        if (!root)
            return;
        vector<int> val;
        order_1(root, val);
        TreeNode* new_root = add(val);
        root->val = new_root->val;
        root->left = nullptr;
        root->right = new_root->right;
        delete new_root;
    }
};
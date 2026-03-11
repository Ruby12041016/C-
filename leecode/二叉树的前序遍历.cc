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
    void preorderTraversal(TreeNode* root, vector<int>& val) {
        if (!root) {
            return;
        }
        val.push_back(root->val);
        preorderTraversal(root->left, val);
        preorderTraversal(root->right, val);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> val;
        preorderTraversal(root, val);
        return val;
    }
};
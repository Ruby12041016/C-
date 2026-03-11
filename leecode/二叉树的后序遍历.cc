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
    void postorderTraversal(TreeNode* root, vector<int>& val) {
        if (!root)
            return;
        postorderTraversal(root->left, val);
        postorderTraversal(root->right, val);
        val.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> val;
        postorderTraversal(root, val);
        return val;
    }
};
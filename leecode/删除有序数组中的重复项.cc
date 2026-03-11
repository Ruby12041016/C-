#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    int removeDuplicates(vector<int>& nums) {
        stack<int> stk;
        for (int i : nums) {
            if (stk.empty() || i != stk.top()) {
                stk.push(i);
            }
        }
        int len = stk.size();
        for (int i = stk.size() - 1; i >= 0; i--) {
            nums[i] = stk.top();
            stk.pop();
        }
        return len;
    }
};
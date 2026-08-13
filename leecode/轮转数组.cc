#include <vector>
#include <stack>
class Solution {
   public:
    void rotate(std::vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0)
            return;
        // 防止k大于数组长度，取余得到实际移动的步数
        int steps = k % n;
        std::stack<int> st1;
        std::stack<int> st2;
        for (int i = 0; i < n; i++) {
            st1.push(nums[i]);
        }
        for (int i = 0; i < steps; i++) {
            st2.push(st1.top());
            st1.pop();
        }
        for (int i = n - 1; i >= steps; i--) {
            nums[i] = nums[i - steps];
        }
        for (int i = 0; i < steps; i++) {
            nums[i] = st2.top();
            st2.pop();
        }
    }
};
#include <vector>
class Solution {
   public:
    int minOperations(std::vector<int>& nums) {
        int n = nums.size();
        int result = 0;
        for (int i = 0; i < n - 2; i++) {
            if (nums[i] == 0) {
                nums[i + 1] ^= 1;
                nums[i + 2] ^= 1;
                result++;
            }
        }
        if (nums[n - 1] == 1 && nums[n - 2] == 1) {
            return result;
        }
        return -1;
    }
};

/*给你一个二进制数组 nums 。

你可以对数组执行以下操作 任意 次（也可以 0 次）：

选择数组中 任意连续 3 个元素，并将它们 全部反转 。
反转 一个元素指的是将它的值从 0 变 1 ，或者从 1 变 0 。

请你返回将 nums 中所有元素变为 1 的 最少 操作次数。如果无法全部变成 1 ，返回 -1
。*/

/*对i操作即i，i+1，i+2都反转，那么很容易得出对i操作两次是无效的。因此对i(就是把i和后面两个反转，i表示i操作)最多操作一次。
由于i是最前的，所以一旦i为0，就必须反转（因为i+1的操作无法使i从0变1）。
最后返回答案时，最后两个必须为1，或者说对第n-3个操作的时候，后三个必然相等，否则答案不可能成立*/
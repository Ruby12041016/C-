#include <vector>
#include <stdlib.h>
#include <algorithm>
class Solution {
   public:
    int maximumGap(std::vector<int>& nums) {
        int max_ = 0;
        int size = nums.size();
        sort(nums.begin(), nums.end());
        if (size < 2) {
            return 0;
        }
        for (int i = 0; i < size - 1; i++) {
            if ((abs(nums[i + 1] - nums[i])) > max_) {
                max_ = abs(nums[i + 1] - nums[i]);
            }
        }
        return max_;
    }
};

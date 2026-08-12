#include <vector>
#include <unordered_map>

class Solution {
   public:
    int singleNumber(std::vector<int>& nums) {
        std::unordered_map<int, int> count;
        for (int i = 0; i < nums.size(); i++) {
            count[nums[i]]++;
        }
        int result = 0;
        for (auto [num, cnt] : count) {
            if (cnt == 1) {
                result = num;
                break;
            }
        }
        return result;
    }
};

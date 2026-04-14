#include <vector>
#include <deque>
class Solution {
   public:
    long long continuousSubarrays(std::vector<int>& nums) {
        std::deque<int> max_, min_;
        int left = 0;
        long long result = 0;
        for (int right = 0; right < nums.size(); right++) {
            int x = nums[right];
            while (!min_.empty() && x <= nums[min_.back()]) {
                min_.pop_back();                                  /*保证从大到小*/
            }
            min_.push_back(right);
            while (!max_.empty() && x >= nums[max_.back()]) {
                max_.pop_back();                                 /*保证从小到大*/
            }                                               
            max_.push_back(right);
            while (nums[max_.front()] - nums[min_.front()] >2) {
                left++;
                if (max_.front() < left) {
                    max_.pop_front();
                }
                if (min_.front() < left) {
                    min_.pop_front();
                }
            }
            result += right - left + 1;
        }
        return result;
    }
};

/*while ( nums[max_.front()] - nums[min_.front()] >2) */
/*因为子数组是原窗口的子数组，所以它的最大值<=原窗口最大值，最小值>=原窗口最小值，所以差值<=原窗口差值，所以如果原窗口满足条件，子数组也满足条件*/
/*所以，我们通过滑动窗口维护一个最小的左端点left，使得[left,right]满足条件，那么对于这个右端点，左端点可以是left, left+1, ...,right，一共right-left+1个*/
#include <vector>
using namespace std;

class Solution {
   public:
    void sortColors(vector<int>& nums) {
        int p1 = 0, p2 = 0;
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];
            nums[i] = 2;
            if (x <= 1) {
                nums[p2++] = 1;
            }
            if (x == 0) {
                nums[p1++] = 0;
            }
        }
    }
};

/*插入排序*/
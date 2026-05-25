#include <vector>
using namespace std;

class Solution {
   public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        for (int i = 0; i < m; i++) {
            if (matrix[i][n - 1] == target || matrix[i][0] == target) {
                return true;
            }
            if (matrix[i][n - 1] > target && matrix[i][0] < target) {
                for (int j = 0; j < n; j++) {
                    if (matrix[i][j] == target) {
                        return true;
                    }
                    if (j == n - 1 && matrix[i][n - 1] != target) {
                        break;
                    }
                }
            }
            if (matrix[i][n - 1] < target && matrix[i][0] > target) {
                break;
            }
        }
        return false;
    }
};

/*给你一个满足下述两条属性的 m x n 整数矩阵：

每行中的整数从左到右按非严格递增顺序排列。
每行的第一个整数大于前一行的最后一个整数。
给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。

*/
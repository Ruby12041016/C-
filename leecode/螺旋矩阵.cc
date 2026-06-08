#include <vector>
using namespace std;

class Solution {
    static constexpr int DIRS[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

   public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int h = matrix.size();
        int l = matrix[0].size();
        vector<int> result;
        int size = h * l;
        int i = 0, j = -1;
        for (int k = 0; result.size() < size; k = (k + 1) % 4) {
            for (int m = 0; m < l; m++) {
                i += DIRS[k][0];
                j += DIRS[k][1];
                result.push_back(matrix[i][j]);
            }
            h--;
            swap(l, h);
        }
        return result;
    }
};
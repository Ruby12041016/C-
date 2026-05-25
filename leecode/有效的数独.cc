#include <vector>
using namespace std;

class Solution {
   public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool row_has[9][9]{};  //行有没有x
        bool col_has[9][9]{};   //列有没有x
        bool map_has[3][3][9]{}; //3x3阵有没有x
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char c = board[i][j];
                if (c == '.') {
                    continue;
                }
                int x = c - '1';
                if (row_has[i][x] || col_has[j][x] ||
                    map_has[i / 3][j / 3][x]) {
                    return false;
                }
                row_has[i][x] = col_has[j][x] = map_has[i / 3][j / 3][x] = 1;
            }
        }
        return true;
    }
};

/*请你判断一个 9 x 9 的数独是否有效。只需要 根据以下规则
，验证已经填入的数字是否有效即可。

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）


注意：

一个有效的数独（部分已被填充）不一定是可解的。
只需要根据以上规则，验证已经填入的数字是否有效即可。
空白格用 '.' 表示*/
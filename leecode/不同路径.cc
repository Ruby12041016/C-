#include <vector>
using namespace std;
class Solution {
   public:
    int dfs(int m, int n, vector<vector<int>>& memo) {
        if (m < 0 || n < 0) {
            return 0;
        }
        if (m == 0 && n == 0) {
            return 1;
        }
        int& res = memo[m][n];
        if (res) {
            return res;
        }
        return res = dfs(m - 1, n, memo) + dfs(m, n - 1, memo);
    }
    int uniquePaths(int m, int n) {
        vector<vector<int>> memo(m, vector<int>(n, 0));
        return dfs(m - 1, n - 1, memo);
    }
};

/*一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为
“Finish” ）。

问总共有多少条不同的路径？*/

/*递归搜索 + 保存递归返回值 = 记忆化搜索
考虑到整个递归过程中有大量重复递归调用（递归入参相同）。由于递归函数没有副作用，同样的入参无论计算多少次，算出来的结果都是一样的，因此可以用记忆化搜索来优化：

如果一个状态（递归入参）是第一次遇到，那么可以在返回前，把状态及其结果记到一个memo 数组中。 如果一个状态不是第一次遇到（memo 中保存的结果不等于 memo的初始值），那么可以直接返回 memo 中保存的结果。

*/
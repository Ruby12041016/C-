#include <queue>

using namespace std;
class Solution {
   public:
    int findTheWinner(int n, int k) {
        queue<int> que;
        for (int i = 0; i < n; i++) {
            que.push(i + 1);
        }
        while (n > 1) {
            for (int i = 0; i < k - 1; i++) {
                que.push(que.front());
                que.pop();
            }
            n--;
            que.pop();
        }
        return que.front();
    }
};
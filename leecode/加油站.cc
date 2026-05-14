#include <vector>
using namespace std;
class Solution {
   public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int i = 0;
        int n = gas.size();
        while (i < n) {
            int sum_cost = 0;
            int sum_gas = 0;
            int count = 0;
            while (count < n) {
                int j = (i + count) % n;
                sum_cost += cost[j];
                sum_gas += gas[j];
                if (sum_gas < sum_cost) {
                    break;
                }
                count++;
            }
            if (count == n) {
                return i;
            } else {
                i = i + count + 1;
            }
        }
        return -1;
    }
};

/*如果x到达不了y+1，那么x-y之间的点也不可能到达y+1，因为中间任何一点的油都是拥有前面的余量的，所以下次遍历直接从y+1开始,即我们首先检查第0个加油站，并试图判断能否环绕一周；如果不能，就从第一个无法到达的加油站开始继续检查。*/
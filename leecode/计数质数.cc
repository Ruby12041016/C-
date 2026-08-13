#include <vector>
class Solution {
   public:
    int countPrimes(int n) {
        std::vector<char> isPrime(n, 1);
        int result = 0;
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) {
                result++;
                if ((long long)i * i < n) {
                    for (int j = i * i; j < n; j += i) {
                        isPrime[j] = 0;
                    }
                }
            }
        }
        return result;
    }
};
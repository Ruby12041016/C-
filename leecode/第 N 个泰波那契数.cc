class Solution {
   public:
    int tribonacci(int n) {
        if (n == 0) {
            return 0;
        }
        if (n <= 1) {
            return 1;
        }
        int r = 0, s = 0, p = 1, q = 1;
        for (int i = 3; i <= n; i++) {
            r = s;
            s = p;
            p = q;
            q = r + s + p;
        }
        return q;
    }
};
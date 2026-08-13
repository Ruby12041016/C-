class Solution {
public:
    int trailingZeroes(int n) {
        int num5=0;
        int num2=0;
        int m=n;
        while (m) {
            m/=5;
            num5+=m;
        }
        while (n) {
            n/=2;
            num2+=n;
        }
        return num2<num5?num2:num5;
    }
};
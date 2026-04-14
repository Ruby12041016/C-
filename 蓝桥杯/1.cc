
#include <iostream>
using namespace std;
int main() {
    long long sum = 0;
    long long count = 10;  // 前10个数已数

    for (long long i = 122;; i++) {
        // 去掉 if(i % 2) continue; 这句，因为20或24的倍数一定是偶数
        if ((i % 20 == 0) || (i % 24 == 0)) {
            count++;
            printf("%lld\n", count);
        }
        if (count == 202420242024LL) {
            sum = i;
            break;
        }
    }
    printf("%lld", sum);
    return 0;
}
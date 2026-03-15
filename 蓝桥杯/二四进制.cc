#include <iostream>
using namespace std;

int sum1(int x, int n, int sum) {
    while (x) {
        sum += x % n;
        x /= n;
    }
    return sum;
}

int main() {
    int result = 0;
    for (int i = 1; i <= 2024; i++) {
        if (sum1(i, 2, 0) == sum1(i, 4, 0)) {
            result++;
        }
    }
    cout << result;
    return 0;
}
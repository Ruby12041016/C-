#include <iostream>
using namespace std;

int sum1(int n, int sum) {
    while (n) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
int main() {
    long long num;
    cin >> num;

    int minute = 0;
    while (num) {
        int num_before = num;
        num -= sum1(num, 0);
        minute++;
    }
    cout << minute;
    return 0;
}
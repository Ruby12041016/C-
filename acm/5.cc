#include <iostream>
#include <vector>
using namespace std;

/*计算数字的位数
 * 根据题目条件，a_i <= 10，所以只需要处理1位或2位的情况
 */
int len(int x) {
    if (x < 10)
        return 1;  // 一位数
    else
        return 2;  // 两位数（题目中a_i <= 10）
}

int main() {
    int N;             // 输入的数字个数
    cin >> N;          
    vector<int> a(N);  // 存储输入的数字
    for (int i = 0; i < N; i++)
        cin >> a[i];  // 读取N个数字

    int ans = 0;  // 计数器，记录符合条件的数对数量

    // 遍历所有可能的数对(i, j)，i和j可以不同
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j)  // 跳过i等于j的情况
                continue;

            int num = a[i];     // 以a[i]作为前半部分
            int l = len(a[j]);  // 计算a[j]的位数

            // 将a[i]左移l位（乘以10^l），为a[j]腾出位置
            for (int k = 0; k < l; k++)
                num *= 10;

            num += a[j];  // 将a[j]拼接到num的末尾

            // 检查拼接后的数字是否能被36整除
            if (num % 36 == 0)
                ans++;  // 如果可以，计数器加1
        }
    }

    cout << ans << endl;  // 输出符合条件的数对数量
    return 0;
}
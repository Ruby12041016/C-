/*题目描述
从 X 星截获一份电码，是一些数字，如下：
13
1113
3113
132113
1113122113
⋯
⋯
YY 博士经彻夜研究，发现了规律：
第一行的数字随便是什么，以后每一行都是对上一行"读出来"
比如第 2 行，是对第 1 行的描述，意思是：1 个 1，1 个 3，所以是：1113
第 3 行，意思是：3 个 1,1 个 3，所以是：3113
请你编写一个程序，可以从初始数字开始，连续进行这样的变换。
输入描述
第一行输入一个数字组成的串，不超过 100 位。
第二行，一个数字n，表示需要你连续变换多少次，n 不超过 20。
输出描述
输出一个串，表示最后一次变换完的结果。*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    string ss;
    int b;
    cin >> ss >> b;
    while (b--) {
        string s1;
        int len = ss.length();
        int count = 1;
        for (int i = 0; i < len; i++) {
            if (i + 1 < len && ss[i] == ss[i + 1]) {
                count++;
            } else {
                s1 += to_string(count) + ss[i];
                count = 1;
            }
        }
        ss = s1;  //更新
    }
    cout << ss;
    return 0;
}

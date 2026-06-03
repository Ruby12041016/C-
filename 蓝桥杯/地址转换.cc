/*题目描述
Excel 是最常用的办公软件。每个单元格都有唯一的地址表示。比如：第 12 行第 4
列表示为："D12"，第 5 行第 255 列表示为"IU5"。
事实上，Excel 提供了两种地址表示方法，还有一种表示法叫做 RC 格式地址。第 12 行第
4 列表示为："R12C4"，第 5 行第 255 列表示为"R5C255"。
你的任务是：编写程序，实现从 RC 地址格式到常规地址格式的转换。
输入描述
用户先输入一个整数n(n<100），表示接下来有n 行输入数据。
接着输入的n行数据是 RC 格式的 Excel 单元格地址表示法。
输出描述
程序则输出n行数据，每行是转换后的常规地址表示法。*/

/*用户输入：
2
R12C4
R5C255

输出：
D12
IU5
*/


#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    while (n--) {
        int a, b;
        char x, y;
        cin >> x >> a >> y >> b;   //关键点：把输入分为了四部分
        if (b <= 26) {
            char c = 'A' + b - 1;
            cout << c << a << endl;
        } else {
            char c = 'A' + b / 26 - 1;
            char d = 'A' + b % 26 - 1;
            cout << c << d << a << endl;
        }
    }
    return 0;
}

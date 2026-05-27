/*题目描述
X 星球的机器人表演拉拉队有两种服装，A 和 B。
他们这次表演的是搭机器人塔。
类似：
A
B B
A B A
A A B B
B B B A B
A B A B B A
队内的组塔规则是：
A只能站在AA或BB的肩上。
B只能站在AB或BA的肩上。
你的任务是帮助拉拉队计算一下，在给定A与B的人数时，可以组成多少种花样的塔。
输入描述
输入一行两个整数
M,N（0<M,N<500）,分别表示A、B的人数，保证人数合理性。
输出描述
要求输出一个整数，表示可以产生的花样种数。*/

#include <bits/stdc++.h>
using namespace std;

char Map[50][50];
int num_a, num_b, line;
long long ans = 0;

bool check() {  // 检查构造出来的是否符合要求，遍历整个三角形统计 'A' 和 'B'的个数，与输入目标比较，完全一致则返回 true。
    int a = 0, b = 0;
    for (int i = 1; i <= line; i++) {
        for (int j = 1; j <= i; j++) {
            if (Map[i][j] == 'A')
                a++;
            else
                b++;
        }
    }
    if (num_a == a && num_b == b)
        return true;
    return false;
}

void init() {  // 根据底层向上延伸
    for (int i = line; i >= 2; i--) {
        for (int j = 1; j < i; j++) {
            if (Map[i][j] == Map[i][j + 1])
                Map[i - 1][j] = 'A';  // 如果下面两个格子相同，则本格子是 'A'
            else
                Map[i - 1][j] = 'B';  // 如果下面两个格子不同，则本格子是 'B'
        }
    }
}

void dfs(int n) {
    if (n == line + 1) {
        init();  // 根据底层生成整个三角形
        if (check()) {
            ans++;  // 统计 A、B 数量是否符合目标
        }
        return;
    }
    Map[line][n] = 'A';
    dfs(n + 1);
    Map[line][n] = 'B'; //直接覆盖，隐含了回溯
    dfs(n + 1);
}

int main() {
    cin >> num_a >> num_b;
    int temp = sqrt(1 + 8 * (num_a + num_b));
    line = (temp - 1) / 2;
    dfs(1);
    cout << ans << endl;

    return 0;
}
/*设三角形行数为 line，总格子数 S = line * (line + 1) / 2。
由 S = num_a + num_b，
代码中先计算 temp = sqrt(1 + 8 * S)，再 line = (temp - 1) / 2。
这里假设输入一定合法（总格子数恰好是三角形数）。*/
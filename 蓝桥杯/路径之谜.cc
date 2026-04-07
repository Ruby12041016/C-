/*题目描述
小明冒充X 星球的骑士，进入了一个奇怪的城堡。
城堡里边什么都没有，只有方形石头铺成的地面。
假设城堡地面是n×n 个方格。
按习俗，骑士要从西北角走到东南角。可以横向或纵向移动，但不能斜着走，也不能跳跃。每走到一个新方格，就要向正北方和正西方各射一箭。（城堡的西墙和北墙内各有n
个靶子）同一个方格只允许经过一次。但不必走完所有的方格。如果只给出靶子上箭的数目，你能推断出骑士的行走路线吗？有时是可以的，比如上图中的例子。
本题的要求就是已知箭靶数字，求骑士的行走路径（测试数据保证路径唯一）
输入描述
第一行一个整数N(0≤N≤20)，表示地面有N×N个方格。
第二行N个整数，空格分开，表示北边的箭靶上的数字（自西向东）
第三行N个整数，空格分开，表示西边的箭靶上的数字（自北向南）
输出描述
输出一行若干个整数，表示骑士路径。*/

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

const int N = 21;
int n;
int nor[N];
int we[N];
int vis[N][N] = {0};
int step[N * N];
// int count=0;
int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
bool found = false;

void dfs(int x, int y, int count) {
    if (found)
        return;
    if (x == n - 1 && y == n - 1) {
        for (int i = 0; i < n; i++) {
            if (nor[i] != 0 || we[i] != 0)
                return;
        }
        found = true;
        for (int i = 0; i < count; i++) {
            printf("%d ", step[i]);
        }
        printf("\n");
        return;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        if (nx >= n || ny >= n || nx < 0 || ny < 0 || vis[nx][ny] ||
            nor[ny] <= 0 || we[nx] <= 0)
            continue;
        else {
            vis[nx][ny] = 1;
            step[count] = nx * n + ny;
            nor[ny]--;
            we[nx]--;
            dfs(nx, ny, count + 1);
            if (found)
                return;
            nor[ny]++;
            we[nx]++;
            vis[nx][ny] = 0;
        }
    }
    return;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nor[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &we[i]);
    }
    vis[0][0] = 1;
    nor[0]--;
    we[0]--;
    step[0] = 0;
    dfs(0, 0, 1);
    return 0;
}
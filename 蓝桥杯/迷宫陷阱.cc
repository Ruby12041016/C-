/*题目描述
小明在玩一款迷宫游戏，在游戏中他要控制自己的角色离开一间由N×N 个格子组成的 2D 迷宫。
小明的起始位置在左上角，他需要到达右下角的格子才能离开迷宫。
每一步，他可以移动到上下左右相邻的格子中（前提是目标格子可以经过）。
迷宫中有些格子小明可以经过，我们用 '.' 表示。
有些格子是墙壁，小明不能经过，我们用 '#' 表示。
此外，有些格子上有陷阱，我们用 'X' 表示。除非小明处于无敌状态，否则不能经过。
有些格子上有无敌道具，我们用 '%' 表示。
当小明第一次到达该格子时，自动获得无敌状态，无敌状态会持续K 步。
之后如果再次到达该格子不会获得无敌状态了。
处于无敌状态时，可以经过有陷阱的格子，但是不会拆除/毁坏陷阱，即陷阱仍会阻止没有无敌状态的角色经过。
给定迷宫，请你计算小明最少经过几步可以离开迷宫?
输入描述
第一行包含两个整数N,K(1≤N≤1000,1≤K≤10)
以下N 行包含一个N×N 的矩阵。
矩阵保证左上角和右下角是 '.'。
输出描述
一个整数表示答案。如果小明不能离开迷宫，输出 -1。*/

#include <bits/stdc++.h>
#include <iostream>
#include <queue>
using namespace std;

char mp[1001][1001];         // 存储地图
bool visit_[1001][1001][12];  // 三维访问数组：位置(x,y)+无敌步数inv
bool vis[1001][1001];        // 记录是否获得过该格子的道具
int dx[] = {-1, 0, 1, 0};    // 上下左右方向
int dy[] = {0, -1, 0, 1};
int n, k;

struct Node {
    int x, y;
    int step;
    int inv;
};

int bfs() {
    memset(visit_, 0, sizeof(visit_));
    memset(vis, 0, sizeof(vis));
    queue<Node> q;
    q.push({1, 1, 0, 0});
    visit_[1][1][0] = true;
    while (q.size()) {
        auto [x, y, step, inv] = q.front();
        q.pop();
        if (x == n && y == n) {
            return step;
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > n)
                continue;
            int new_inv = max(0, inv - 1);
            char ch = mp[nx][ny];
            if (ch == '#')
                continue;
            if (ch == 'X') {
                if (inv == 0)
                    continue;
            }
            if (ch == '%') {
                if (!vis[nx][ny]) {
                    new_inv = k;
                    vis[nx][ny] = true;
                }
            }
            if (!visit_[nx][ny][new_inv]) {
                visit_[nx][ny][new_inv] = true;
                q.push({nx, ny, step + 1, new_inv});
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf(" %c", &mp[i][j]);
        }
    }
    printf("%d", bfs());
    return 0;
}
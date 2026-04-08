/*
小蓝最近迷上了一款名为《数字接龙》的迷宫游戏，游戏在一个大小为N×N 的格子棋盘上展开，其中每一个格子处都有着一个0…K−1 之间的整数。游戏规则如下：
从左上角(0,0) 处出发，目标是到达右下角(N−1,N−1) 处的格子，每一步可以选择沿着水平/垂直/对角线方向移动到下一个格子。
对于路径经过的棋盘格子，按照经过的格子顺序，上面的数字组成的序列要满足：
0,1,2,…,K−1,0,1,2,…,K−1,0,1,2… 。
途中需要对棋盘上的每个格子恰好都经过一次（仅一次）。
路径中不可以出现交叉的线路。例如之前有从(0,0) 移动到(1,1) ，那么再从(1,0) 移动到(0,1) 线路就会交叉。
为了方便表示，我们对可以行进的所有八个方向进行了数字编号；因此行进路径可以用一个包含0…7 之间的数字字符串表示。
现在请你帮小蓝规划出一条行进路径并将其输出。如果有多条路径，输出字典序最小的那一个；如果不存在任何一条路径，则输出−1。
输入格式
第一行包含两个整数N,K 。
接下来输入N 行，每行N 个整数表示棋盘格子上的数字。
输出格式
输出一行表示答案。如果存在答案输出路径，否则输出−1。
*/

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

const int N = 12;
int mp[N][N];
int n, k;
string path;
int dir[8][2]{{-1, 0}, {-1, 1}, {0, 1},  {1, 1},
              {1, 0},  {1, -1}, {0, -1}, {-1, -1}};
bool vis[N][N] = {false};
bool edge[N][N][N][N] = {false};
bool found;
int count_ = 0;  //变量名count与C++标准库中的std::count函数冲突了。
void dfs(int x, int y) {     //当使用了#include<bits/stdc++.h>时包含了整个标准库，其中包括了std::count函数。
    if (found)
        return;
    if ((x == n - 1) && (y == n - 1) && (count_ == n * n)) {
        found = true;
        // path.push_back('\0');  不必要，而且可能导致输出包含空字符
        cout << path;
        return;
    }
    for (int i = 0; i < 8; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        if (mp[x][y] == k - 1) {
            if (mp[nx][ny] != 0)
                continue;
        } else {
            if (mp[nx][ny] - mp[x][y] != 1)
                continue;
        }
        if (nx < 0 || nx >= n || ny < 0 || ny >= n)
            continue;
        if (i % 2 && (edge[x][ny][nx][y] || edge[nx][y][x][ny]))
            continue;
        if (vis[nx][ny])
            continue;
        vis[nx][ny] = true;
        edge[x][y][nx][ny] = true;
        path += i + '0';
        count_++;
        dfs(nx, ny);
        count_--;
        vis[nx][ny] = false;
        path.pop_back();
        edge[x][y][nx][ny] = false;
    }
    return;
}

int main() {
    found = false;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &mp[i][j]);
        }
    }
    vis[0][0] = true;
    count_ = 1;
    dfs(0, 0);
    return 0;
}
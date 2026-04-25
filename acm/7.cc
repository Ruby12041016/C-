#include <cstring>   // 包含memset函数
#include <iostream>  
#include <queue>    
using namespace std;

const int MAXN = 1005;    // 迷宫的最大尺寸
char maze[MAXN][MAXN];    // 存储迷宫
bool vis[MAXN][MAXN][4];  // 访问标记，状态为 (x, y, dir)，dir表示当前面向的方向
int n, m;                 // 迷宫的行数和列数
int sx, sy, tx, ty;       // 起点坐标(sx, sy)和终点坐标(tx, ty)

// 方向数组，顺序为：上(0), 右(1), 下(2), 左(3)
int dx[4] = {-1, 0, 1, 0};  // x方向的偏移量
int dy[4] = {0, 1, 0, -1};  // y方向的偏移量

// 队列中的节点结构
struct Node {
    int x, y, dir;  // x和y是坐标，dir是当前面向的方向
};

/*
 * 使用BFS算法判断从起点S到终点T是否存在路径
 * 移动规则：可以直行或左转
 */
bool bfs() {
    memset(vis, 0, sizeof(vis));  // 初始化访问标记为false
    queue<Node> q;                // 创建队列

    // 从起点出发，尝试所有4个可能的初始方向
    for (int d = 0; d < 4; d++) {
        q.push({sx, sy, d});    // 将起点的每个方向状态入队
        vis[sx][sy][d] = true;  // 标记为已访问
    }

    while (!q.empty()) {       // 当队列不为空时
        Node cur = q.front();  // 取出队首元素
        q.pop();               // 出队

        // 如果到达终点，返回true
        if (cur.x == tx && cur.y == ty)
            return true;

        // 尝试直行
        int nx = cur.x + dx[cur.dir];  // 计算直行后的x坐标
        int ny = cur.y + dy[cur.dir];  // 计算直行后的y坐标
        // 检查新位置是否在迷宫范围内且不是障碍物
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[nx][ny] != '#') {
            // 如果该状态未访问过
            if (!vis[nx][ny][cur.dir]) {
                vis[nx][ny][cur.dir] = true;  // 标记为已访问
                q.push({nx, ny, cur.dir});    // 入队
            }
        }

        // 尝试左转
        int ndir = (cur.dir + 3) % 4;  // 计算左转后的方向（+3相当于-1，模4）
        nx = cur.x + dx[ndir];         // 计算左转后的x坐标
        ny = cur.y + dy[ndir];         // 计算左转后的y坐标
        // 检查新位置是否在迷宫范围内且不是障碍物
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[nx][ny] != '#') {
            // 如果该状态未访问过
            if (!vis[nx][ny][ndir]) {
                vis[nx][ny][ndir] = true;  // 标记为已访问
                q.push({nx, ny, ndir});    // 入队
            }
        }
    }

    return false;  // 遍历完所有可能的状态后仍未到达终点，返回false
}

int main() {
    cin >> n >> m;  // 读取迷宫的行数和列数
    for (int i = 0; i < n; i++)
        cin >> maze[i];  // 读取每一行的迷宫数据

    // 寻找起点S和终点T的坐标
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maze[i][j] == 'S')  // 找到起点
                sx = i, sy = j;
            if (maze[i][j] == 'T')  // 找到终点
                tx = i, ty = j;
        }
    }

    // 使用BFS判断是否存在路径
    if (bfs())
        cout << "YES" << endl;  // 存在路径
    else
        cout << "NO" << endl;  // 不存在路径

    return 0;
}
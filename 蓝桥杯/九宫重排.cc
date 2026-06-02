/*题目描述
如下图的九宫格中，放着 1 ~ 8
的数字卡片，还有一个格子空着。与空格子相邻的格子中的卡片可以移动到空格中。
经过若干次移动，可以形成图2所示的局面。
我们把上图的局面记为：12345678.
把下图的局面记为：123.46758
显然是按从上到下，从左到右的顺序记录数字，空格记为句点。
题目的任务是已知九宫的初态和终态，求最少经过多少步的移动可以到达。如果无论多少步都无法到达，则输出-1。
输入描述
输入第一行包含九宫的初态，第二行包含九宫的终态。
输出描述
输出最少的步数，如果不存在方案，则输出 -1。
*/

#include <bits/stdc++.h>
using namespace std;

string s1, s2;
map<string, int> mp;  // map<string, int> mp：记录从初始状态到达某个状态的最短步数，同时起到去重作用（避免重复搜索）。
int dir[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};
void bfs() {
    queue<string> q;  // queue<string> q：BFS队列，存放待扩展的状态。
    q.push(s1);
    mp[s1] = 0;
    while (!q.empty()) {
        string p = q.front();
        q.pop();
        int dist = mp[p];
        if (p == s2) {
            cout << mp[s2];
            return;
        }
        int k = p.find('.');
        int x = k / 3, y = k % 3;
        int tx, ty;
        for (int i = 0; i < 4; i++) {
            tx = x + dir[i][0];
            ty = y + dir[i][1];
            if (tx < 0 || tx > 2 || ty < 0 || ty > 2)
                continue;
            int tk = tx * 3 + ty;
            swap(p[k], p[tk]);
            if (mp.count(p) == 0) {
                mp[p] = dist + 1;
                q.push(p);
            }
            swap(p[k], p[tk]);
        }
    }
}
/*初始状态入队，步数记为 0。
循环取出队首状态 p，获取当前步数 dist。
如果 p == s2，说明找到目标，输出步数并返回。
找到空格 '.' 在字符串中的位置 k，计算它的二维坐标：
int x = k / 3, y = k % 3;
尝试四个方向移动空格：
计算新坐标 (tx, ty)，边界检查。
将新坐标转回一维索引 tk = tx * 3 + ty。
交换空格和新位置对应的字符，得到新状态。
若该状态未访问过（mp.count(p) == 0），则记录步数 dist + 1，入队。
恢复交换（回溯），以便尝试其他方向。*/
int main() {
    cin >> s1 >> s2;
    bfs();
}


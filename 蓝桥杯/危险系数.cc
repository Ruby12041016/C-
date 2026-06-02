/*题目描述
抗日战争时期，冀中平原的地道战曾发挥重要作用。
地道的多个站点间有通道连接，形成了庞大的网络。但也有隐患，当敌人发现了某个站点后，其它站点间可能因此会失去联系。
我们来定义一个危险系数DF(x,y)：
对于两个站点x和y(x!=y), 如果能找到一个站点z，当z 被敌人破坏后,x和y不连通，那么我们称z为关于x,y的关键点。
相应的，对于任意一对站点x和y，危险系数DF(x,y) 就表示为这两点之间的关键点个数。
本题的任务是：已知网络结构，求两站点之间的危险系数。
输入描述
输入数据第一行包含2个整数n(2≤n≤1000),m(0≤m≤2000),分别代表站点数，通道数；
接下来m行，每行两个整数u,v(1≤u,v≤n,u!=v) 代表一条通道；
最后 1 行，两个数u,v，代表询问两点之间的危险系数DF(u,v)。
输出描述
输出一个整数，如果询问的两点不连通则输出 -1.*/

#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int map[1009];          // 路径
int num[1009];          // 每个站点被经过的次数
vector<int> cnt[1009];  // 通道
bool vis[1009];         // 标记站点是否被经过
int n, m;
int X, Y;
int ans = 0;
void dfs(int x, int t) {
    if (x == Y) {
        ans++;
        for (int i = 1; i < t; i++) {
            num[map[i]]++;
        }
        return;
    }
    int N = cnt[x].size();
    for (int i = 0; i < N; i++) {
        if (vis[cnt[x][i]] == false) {
            vis[cnt[x][i]] = true;
            map[t] = cnt[x][i];
            dfs(cnt[x][i], t + 1);
            vis[cnt[x][i]] = false;
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        cnt[a].push_back(b);
        cnt[b].push_back(a);
    }
    cin >> X >> Y;
    vis[X] = true;
    dfs(X, 1);
    if (ans == 0) {
        cout << "-1" << endl;
    } else {
        int k = 0;
        for (int i = 1; i <= n; i++) {
            if (num[i] == ans) {
                k++;
            }
        }
        cout << k - 1 << endl;
    }
    return 0;
}

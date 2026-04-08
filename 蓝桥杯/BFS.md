# BFS（广度优先搜索）

## 一、BFS是什么？

BFS是一种**逐层扩展**的搜索算法，从起点开始，**先搜索所有距离为1的点，再搜索距离为2的点**，以此类推。

**核心思想**：用**队列**实现，先进先出。

---

## 二、BFS解决什么问题？

1. **迷宫最短路径**（无权图）
2. **最少步数问题**
3. **连通块问题**
4. **树/图的层次遍历**

---

## 三、BFS模板（必须背熟！）

```cpp
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

typedef pair<int, int> PII;  // 存储坐标
const int N = 110;

int n, m;
int g[N][N];    // 地图
int dist[N][N]; // 距离
PII pre[N][N];  // 记录路径（可选）

int bfs() {
    queue<PII> q;
    memset(dist, -1, sizeof dist);  // 初始化为-1表示未访问
    
    dist[0][0] = 0;      // 起点距离为0
    q.push({0, 0});      // 起点入队
    
    int dx[4] = {-1, 0, 1, 0};  // 上下左右
    int dy[4] = {0, 1, 0, -1};
    
    while(!q.empty()) {
        auto t = q.front();  // 取队头
        q.pop();
        
        int x = t.first, y = t.second;
        
        // 到达终点
        if(x == n-1 && y == m-1) {
            return dist[x][y];
        }
        
        // 向四个方向扩展
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            // 判断合法性：不越界、能走、未访问
            if(nx >= 0 && nx < n && ny >= 0 && ny < m 
               && g[nx][ny] == 0 && dist[nx][ny] == -1) {
                
                dist[nx][ny] = dist[x][y] + 1;  // 距离+1
                pre[nx][ny] = {x, y};           // 记录前驱
                q.push({nx, ny});               // 新点入队
            }
        }
    }
    
    return -1;  // 无法到达
}
```

---

## 四、BFS执行过程（图解）

**迷宫示例**：
```
起点(0,0)    终点(2,2)
0 1 0
0 0 0
0 1 0
(1是障碍)
```

**BFS搜索顺序**：
```
第0步: (0,0)
第1步: (1,0) (0,1) 
第2步: (2,0) (1,1) (0,2)
第3步: (2,1) (1,2)
第4步: (2,2) 到达终点
最短距离：4
```

---

## 五、BFS求最短路径（记录路径）

```cpp
void print_path(int x, int y) {
    if(x == 0 && y == 0) {
        cout << "(0,0)";
        return;
    }
    
    auto p = pre[x][y];  // 前驱节点
    print_path(p.first, p.second);  // 递归打印
    cout << " -> (" << x << "," << y << ")";
}

// 在bfs中找到终点后调用
if(dist[n-1][m-1] != -1) {
    cout << "最短距离：" << dist[n-1][m-1] << endl;
    cout << "路径：";
    print_path(n-1, m-1);
}
```

---

## 六、BFS变形

### 1. 多起点BFS
```cpp
// 把所有起点先入队
for(每个起点) {
    dist[起点] = 0;
    q.push(起点);
}
// 然后正常BFS
```

### 2. 双向BFS（优化）
```cpp
queue<int> q1, q2;  // 两个队列
dist1[起点] = 0; dist2[终点] = 0;
q1.push(起点); q2.push(终点);

while(q1.size() && q2.size()) {
    // 扩展q1
    // 如果遇到dist2中访问过的点，找到答案
    
    // 扩展q2
    // 如果遇到dist1中访问过的点，找到答案
}
```

### 3. 8方向移动
```cpp
int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
```

---

## 七、BFS vs DFS 对比

| 特性 | BFS | DFS |
|------|-----|-----|
| 数据结构 | 队列 | 栈/递归 |
| 空间复杂度 | O(2^h) | O(h) |
| 能找最短路径 | 能（无权图） | 不能保证 |
| 适合问题 | 最短路径、最少步数 | 所有解、连通性 |

---

## 八、常见错误

### 错误1：忘记标记访问
```cpp
// 错误
q.push({nx, ny});  // 没标记就入队，会重复访问

// 正确
dist[nx][ny] = dist[x][y] + 1;  // 先标记
q.push({nx, ny});               // 再入队
```

### 错误2：判断条件错误
```cpp
// 错误：先判断坐标，再访问数组
if(g[nx][ny]==0 && nx>=0 && nx<n && ny>=0 && ny<m)
// 可能越界访问g数组

// 正确：先判断坐标范围
if(nx>=0 && nx<n && ny>=0 && ny<m && g[nx][ny]==0)
```

### 错误3：起点没初始化
```cpp
// 错误
q.push({0, 0});
// 忘记设置dist[0][0] = 0

// 正确
dist[0][0] = 0;
q.push({0, 0});
```

---

## 九、实战例题

### 例题1：迷宫最短路径
```cpp
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int N = 110;
int n, m;
int g[N][N], d[N][N];  // g是地图，d是距离
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int bfs() {
    queue<pair<int,int>> q;
    memset(d, -1, sizeof d);
    d[0][0] = 0;
    q.push({0, 0});
    
    while(q.size()) {
        auto t = q.front(); q.pop();
        int x = t.first, y = t.second;
        
        // 重要：判断是否是终点
        if(x == n-1 && y == m-1) {
            return d[x][y];  // 找到终点，立即返回
        }
        
        for(int i=0; i<4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx>=0 && nx<n && ny>=0 && ny<m && g[nx][ny]==0 && d[nx][ny]==-1) {
                d[nx][ny] = d[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    return -1;  // 如果队列空了还没找到，返回-1表示不可达
}

int main() {
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> g[i][j];
    cout << bfs() << endl;
    return 0;
}
```

### 例题2：走马（象棋马走日）
```cpp
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
// 其他和普通BFS一样
```

---

## 十、BFS解题步骤

1. **定义状态**：用什么表示一个节点？(x,y)坐标？还是其他？
2. **确定起点和终点**：从哪里开始，到哪里结束
3. **定义移动方式**：上下左右？还是其他移动规则？
4. **BFS模板**：
   - 初始化队列，起点入队
   - 标记起点已访问
   - while队列不空：
     - 取队头
     - 如果是终点，返回结果
     - 向各个方向扩展
     - 如果合法且未访问，入队并标记
5. **输出结果**

---

## 十一、记忆口诀

```
BFS用队列，先进先出
起点先入队，标记距离
while队不空，取队头
若是终点就返回
四个方向都尝试
合法未访就入队
距离加一记下来
```

---

## 十二、练习建议

1. **模板题**：迷宫最短路径（必须熟练）
2. **变形题**：多起点、障碍物、传送门
3. **应用**：连通块数量、层序遍历
4. **优化**：双向BFS、A*算法


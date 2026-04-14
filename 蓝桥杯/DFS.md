# DFS（深度优先搜索）

## 一、DFS核心思想
- **一条路走到底**，走不通就回头
- 用**栈**（递归）实现
- 主要用于找**所有解**，不保证最优

## 二、DFS模板

### 模板1：递归实现
```cpp
int path[N];      // 记录路径
bool st[N];       // 标记数组

void dfs(int u) {  // u表示当前层数/位置
    // 1. 终止条件
    if(u == n) {   // 找到解
        处理结果;
        return;
    }
    
    // 2. 遍历所有选择
    for(int i=0; i<选项个数; i++) {
        if(!st[i]) {  // 如果可选
            // 3. 做选择
            st[i] = true;
            path[u] = i;
            
            // 4. 递归
            dfs(u+1);
            
            // 5. 回溯（关键！）
            st[i] = false;
        }
    }
}
```

### 模板2：迷宫/图遍历
```cpp
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
bool st[N][N];

void dfs(int x, int y) {
    st[x][y] = true;  // 标记已访问
    
    for(int i=0; i<4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if(合法且未访问) {
            dfs(nx, ny);
        }
    }
}
```

## 三、回溯的核心
```cpp
// 必须三步：
1. 做选择（标记）
2. 递归
3. 撤销选择（回溯） ← 最容易忘！
```

## 四、DFS vs BFS 对比

| 特性 | DFS | BFS |
|------|-----|-----|
| 数据结构 | 栈/递归 | 队列 |
| 空间 | O(深度) | O(宽度) |
| 最短路径 | 不保证 | 保证（无权图） |
| 适合 | 所有解、连通性 | 最短路径、最少步数 |
| 时间复杂度 | 指数级 | 指数级 |

## 五、常见题型

### 1. 排列组合
```cpp
// 排列
for(int i=1; i<=n; i++) {
    if(!st[i]) {  // 判断是否用过
        st[i] = true;
        dfs(u+1);
        st[i] = false;
    }
}

// 组合（避免重复）
for(int i=start; i<=n; i++) {  // 从start开始
    dfs(u+1, i+1);  // 下一层从i+1开始
}
```

### 2. 子集
```cpp
void dfs(int u) {
    if(u == n) {
        记录当前子集;
        return;
    }
    
    // 选当前元素
    path.push_back(a[u]);
    dfs(u+1);
    path.pop_back();
    
    // 不选当前元素
    dfs(u+1);
}
```

### 3. 连通块（Flood Fill）
```cpp
int dfs(int x, int y) {
    st[x][y] = true;
    int cnt = 1;
    
    for(int i=0; i<4; i++) {
        int nx = x+dx[i], ny = y+dy[i];
        if(合法且未访问) {
            cnt += dfs(nx, ny);
        }
    }
    return cnt;
}
```

## 六、剪枝技巧（优化）

### 1. 可行性剪枝
```cpp
if(当前状态已经不合法) return;
```

### 2. 最优性剪枝
```cpp
if(当前解已经比已知最差) return;
```

### 3. 排序剪枝
```cpp
sort(a, a+n);  // 排序后更容易剪枝
```

### 4. 重复剪枝
```cpp
if(当前状态已经搜过) return;
```

## 七、记忆化搜索
```cpp
int memo[N];  // 记忆数组
int dfs(int u) {
    if(memo[u] != -1) return memo[u];  // 已计算过
    
    int res = 0;
    for(每个选择) {
        res = max/min(res, dfs(下一状态) + 代价);
    }
    
    memo[u] = res;  // 记忆
    return res;
}
```

## 八、易错点

### 错误1：忘记回溯
```cpp
st[i] = true;
dfs(u+1);
// 忘记 st[i] = false;  ❌
```

### 错误2：判断条件顺序
```cpp
// 错误：先判断内容，再判断边界
if(g[nx][ny]==0 && nx>=0)  // 可能越界访问g

// 正确：先判断边界
if(nx>=0 && ny>=0 && g[nx][ny]==0)
```

### 错误3：全局变量污染
```cpp
int sum = 0;
void dfs(int u) {
    sum += a[u];  // 修改全局变量
    dfs(u+1);
    // 忘记 sum -= a[u];  ❌
}
```

## 九、调试技巧

### 1. 打印递归深度
```cpp
void dfs(int u, string indent) {
    cout << indent << "dfs(" << u << ")" << endl;
    // ...
    dfs(u+1, indent + "  ");
}
```

### 2. 打印路径
```cpp
void print_path() {
    for(int i=0; i<path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;
}
```

## 十、时间复杂度分析

- 排列：O(n!)
- 组合：O(2^n)
- 子集：O(2^n)
- 全排列：O(n·n!)

## 十一、蓝桥杯常考题型

1. **全排列**：数字、字母的排列
2. **组合**：从n个中选k个
3. **子集**：所有子集
4. **数独/八皇后**：约束满足
5. **连通块**：岛屿数量、最大面积
6. **路径搜索**：迷宫所有路径

## 十二、代码模板（背！）

```cpp
// 全排列模板
#include <iostream>
using namespace std;

const int N = 10;
int n;
int path[N];
bool st[N];

void dfs(int u) {
    if(u == n) {
        for(int i=0; i<n; i++) cout << path[i] << " ";
        cout << endl;
        return;
    }
    
    for(int i=1; i<=n; i++) {
        if(!st[i]) {
            path[u] = i;
            st[i] = true;
            dfs(u+1);
            st[i] = false;  // 回溯
        }
    }
}

int main() {
    cin >> n;
    dfs(0);
    return 0;
}
```

## 十三、一句话总结

**DFS = 递归 + 回溯 + 剪枝**

记住：
- 递归前**标记**
- 递归后**回溯**
- 及时**剪枝**优化
- 问"所有可能"用DFS
- 问"最短最少"用BFS


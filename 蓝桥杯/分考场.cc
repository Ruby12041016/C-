/*题目描述
n 个人参加某项特殊考试。
为了公平，要求任何两个认识的人不能分在同一个考场。
求至少需要分几个考场才能满足条件。
输入描述
输入格式：
第一行，一个整数n(1≤n≤100)，表示参加考试的人数。
第二行，一个整数m，表示接下来有m行数据。
以下m行每行的格式为：两个整数a,b，用空格分开(1≤a,b≤n)表示第a个人与第b个人认识。
输出描述
输出一行一个整数，表示最少分几个考场。*/

#include <bits/stdc++.h>
using namespace std;

const int N = 150;
bool a[N][N];  //a[x][y] == true 表示学生 x 和 y 认识
int p[N][N];  // p[i][j] = 第 i 个考场的第 j 个座位上坐的是哪位学生，例如p[2][3] = 5 表示第 2 考场的第 3 个座位坐的是 5号学生。如果某个位置没人，值为 0。
int num = N;  // 最终答案，初始化为 N=150（比最大学生数还大），随后在DFS中不断更新为更小的考场数。
int n, m;

//id:当前正在安排的学生编号,class_num:当前开了几间教室
void dfs(int id, int class_num) {
    if (class_num >= num)
        return;  // 如果当前考场数已经 大于等于已知最优解，再往下搜也不可能得到更少的考场数，直接返回（剪掉这个分支）。
    if (id > n) {
        num = min(num, class_num);
        return;
    }  // 当 id 超过 n，说明所有 n 个学生都已安排好座位。此时 class_num就是当前方案使用的考场总数。用 min 更新全局最优 num，然后返回。
    for (int classnum = 1; classnum <= class_num; classnum++) {
        // 在 classNumber 号考场里找一个能和 id 共存的座位
        int classpos = 1;
        while (p[classnum][classpos] && !a[id][p[classnum][classpos]])
            classpos++;
        if (p[classnum][classpos] == 0) {
            p[classnum][classpos] = id;
            dfs(id + 1, class_num);
            p[classnum][classpos] = 0;
        }
    }
    //依次检查已有考场，只要该考场没有任何认识的人，就把 id放在该考场的最末尾。如果所有已有考场都有认识的人，就执行下一步开新考场。
    p[class_num + 1][1] = id;
    dfs(id + 1, class_num + 1);
    p[class_num + 1][1] = 0;
}
int main() {
    scanf("%d", &n);
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int c, b;
        scanf("%d %d", &c, &b);
        a[c][b] = true;
        a[b][c] = true;  // 认识关系是双向的
    }
    dfs(1, 1);
    printf("%d", num);
    return 0;
}
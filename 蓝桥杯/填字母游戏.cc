/*题目描述
小明经常玩 LOL 游戏上瘾，一次他想挑战 K 大师，不料 K 大师说：
"我们先来玩个空格填字母的游戏，要是你不能赢我，就再别玩 LOL 了"。
K 大师在纸上画了一行n个格子，要小明和他交替往其中填入字母。
并且：
轮到某人填的时候，只能在某个空格中填入 L 或 O。
谁先让字母组成了"LOL"的字样，谁获胜。
如果所有格子都填满了，仍无法组成 LOL，则平局。
小明试验了几次都输了，他很惭愧，希望你能用计算机帮他解开这个谜。
输入描述
本题的输入格式为：
第一行，数字n（n<10），表示下面有n 个初始局面。
接下来，n 行，每行一个串，表示开始的局面。
比如："******", 表示有 6 个空格。"L****", 表示左边是一个字母L，它的右边是4
个空格。
输出描述
要求输出n个数字，表示对每个局面，如果小明先填，当K大师总是用最强着法的时候，小明的最好结果。
1 表示能赢；
-1 表示必输；
0 表示可以逼平。*/

#include <bits/stdc++.h>
using namespace std;

string str;          // 当前要评估的局面字符串
map<string, int> m;  // 记录某个局面下的结果，用于记忆化

int game() {
    if (m.count(str) != 0)
        return m[str];  //如果当前局面之前已经搜索过，直接返回结果，避免重复计算。
    if (str.find("LOL") != string::npos)
        return -1;  //对手走完有LOL了，己方输
    else if (str.find('*') == string::npos)
        return 0;  // 若字符串中没有 "*" 且没有"LOL"，说明棋盘已满、无人输，即为平局，返回 0。
    int flag = -1;  // flag 初始为 -1（最坏情况：当前玩家输）
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '*') {
            
            str[i] = 'L';  //走L
            int res = game(); //对方走
            str[i] = '*';  //恢复
            if (res == -1)  //对方输，己方必赢
                return m[str] = 1;
            else if (res ==0)  // 对方可以逼平 => 我方至少能平，将 flag更新为0（但不立刻返回，因为可能还有能让我方赢的走法，需要继续尝试）。
                flag = 0;

            str[i] = 'O'; //走O
            res = game();
            str[i] = '*';
            if (res == -1)
                return m[str] = 1;
            else if (res == 0)
                flag = 0;
        }
    }
    return m[str] = flag;  // 没有赢的走法，返回最好结果（平或输），所有走法试完后，若flag仍为-1说明无论怎么走都会输；若为0说明至少有一种走法能平局，但没有必胜法。
}
int main() {
    int n, index = 0, ans[15];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> str;
        ans[index++] = game();
    }
    for (int i = 0; i < index; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}

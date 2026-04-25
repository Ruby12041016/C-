#include <iostream>
#include <vector>
using namespace std;
int n, k;       // n: 数组长度, k: 子数组最小长度
vector<int> a;  // 存储输入数组

/*检查是否存在长度至少为k的子数组，使得其中大于等于mid的元素个数多于小于mid的元素个数*/
bool check(int mid) {
    vector<int> b(n);  // 转换后的数组，大于等于mid的为1，否则为-1
    for (int i = 0; i < n; i++)
        b[i] = (a[i] >= mid) ? 1 : -1;

    vector<int> pre(n + 1, 0);  // 前缀和数组
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + b[i - 1];

    int min_pre = 0;  // 初始化为pre[0] = 0
    for (int i = k; i <= n; i++) {
        // 检查从i-k+1到i的子数组和是否大于0
        // 即pre[i] - pre[i-k] > 0
        if (pre[i] > min_pre)
            return true;
        // 更新min_pre为前k个前缀和中的最小值
        min_pre = min(min_pre, pre[i - k + 1]);
    }
    return false;
}

int main() {
    cin >> n >> k;  // 读取数组长度和子数组最小长度
    a.resize(n);    // 调整数组大小
    for (int i = 0; i < n; i++)
        cin >> a[i];  

    int l = 1, r = n, ans = 1;  // 二分查找范围，初始答案为1
    while (l <= r) {
        int mid = (l + r) / 2;  // 计算中间值
        if (check(mid)) {       // 如果存在符合条件的子数组
            ans = mid;          // 更新答案
            l = mid + 1;        // 尝试更大的值
        } else {
            r = mid - 1;  // 尝试更小的值
        }
    }
    cout << ans << endl;  // 输出最大的可能值
    return 0;
}
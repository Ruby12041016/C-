#include <algorithm>  // 包含sort函数
#include <iostream>   
#include <vector>     
using namespace std;
typedef long long ll;  

int main() {
    int n, k;          // n: 元素总数, k: 分组数
    cin >> n >> k;     
    vector<int> a(n);  
    for (int i = 0; i < n; i++)
        cin >> a[i];  // 读取n个元素

    sort(a.begin(), a.end());  // 对元素进行排序
    int m = n / k;             // 计算每组的元素个数
    ll ans = 0;                // 存储总距离之和

    // 遍历每个组
    for (int i = 0; i < k; i++) {
        int left = i * m;                    // 当前组的左边界
        int right = left + m - 1;            // 当前组的右边界
        int median = a[(left + right) / 2];  // 计算当前组的中位数

        // 计算组内所有元素到中位数的绝对距离之和
        for (int j = left; j <= right; j++) {
            ans += abs(a[j] - median);
        }
    }

    cout << ans << endl;  // 输出总距离之和
    return 0;
}
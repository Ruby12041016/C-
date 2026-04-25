#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;                  
    cin >> T;               
    while (T--) {           
        int n;              
        string s;           
        cin >> n >> s;     
        long long ans = 0;  
        for (int i = 0; i < n; i++) {  
            if (s[i] == '1') {
                ans += (i + 1) * (n - i);  // 计算该'1'对答案的贡献：(i+1)*(n-i)
            }
        }
        cout << ans << "\n";  // 输出当前测试用例的答案
    }
    return 0;
}
/*对于字符串中的每个'1'（位于位置i，从0开始计数），计算包含它的所有子串的数量：
左边有 i+1 个选择（包括自己）
右边有 n-i 个选择（包括自己）
所以包含该'1'的子串总数为 (i+1)*(n-i)*/
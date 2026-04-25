#include <algorithm>  // 包含__gcd函数
#include <iostream>   
using namespace std;

int main() {
    int T;                   // 测试用例的数量
    cin >> T;                
    while (T--) {            
        int n;               // 数组长度
        cin >> n;            
        int g = 0, sum = 0;  // g: 数组元素的最大公约数, sum: 数组元素的和
        for (int i = 0; i < n; i++) {
            int x;            
            cin >> x;        
            g = __gcd(g, x);  // 更新最大公约数
            sum += x;         // 累加元素到sum
        }
        g = __gcd(g,
                  2);  // 与2取最大公约数，确保g是偶数或保持原g（如果原g是奇数）
        int ans = sum / g + 1;  
        cout << ans << endl;   
    }
    return 0;
}
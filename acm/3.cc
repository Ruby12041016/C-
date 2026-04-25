#include <algorithm>  // 包含min等算法函数
#include <cmath>      // 包含数学函数
#include <iostream>   
using namespace std;
typedef long long ll;  

ll getFactorCnt(ll num, ll p) {
    ll cnt = 0;
    while (num) {
        cnt += num / p;  // 计算num中包含多少个p的倍数
        num /= p;        // 继续计算更高次幂的倍数
    }
    return cnt;
}

/* 计算阶乘 n! 在 k 进制下末尾零的个数
 * 原理：k进制下末尾零的个数取决于k的质因子分解后，各质因子在n!中的个数与k中对应质因子指数的比值的最小值
 */
ll factorialZero(ll n, ll k) {
    ll ans = 9e18;  // 初始化为一个大数，用于存储最小值
    // 分解 k 的质因子
    ll temp = k;
    for (ll p = 2; p * p <= temp; p++) {  // 遍历可能的质因子
        if (temp % p == 0) {              // 如果p是temp的因子
            ll e = 0;                     // 记录p在k中的指数
            while (temp % p == 0) {
                e++;
                temp /= p;
            }
            // 计算n!中包含质因子p的个数
            ll cnt = getFactorCnt(n, p);
            // 更新答案为当前最小值
            ans = min(ans, cnt / e);
        }
    }
    if (temp > 1) {  // 处理剩余的大质因子（如果有的话）
        ll cnt = getFactorCnt(n, temp);
        ans = min(ans, cnt);
    }
    return ans;
}

/* 计算 a^b 在 k 进制下末尾零的个数
 * 原理：类似阶乘的情况，计算a中各质因子的个数，乘以b后与k中对应质因子指数的比值的最小值
 */
ll powerZero(ll a, ll b, ll k) {
    ll ans = 9e18;              // 初始化为一个大数
    ll temp_a = a, temp_k = k;  // 保存原始值，避免修改参数
    // 对 k 分解质因子，并计算 a 中包含的对应质因子个数
    for (ll p = 2; p * p <= temp_k; p++) {  // 遍历可能的质因子
        if (temp_k % p == 0) {              // 如果p是k的因子
            ll e = 0;                       // 记录p在k中的指数
            while (temp_k % p == 0) {
                e++;
                temp_k /= p;
            }
            ll cnt_in_a = 0;  // 记录a中包含质因子p的个数
            while (temp_a % p == 0) {
                cnt_in_a++;
                temp_a /= p;
            }
            // a^b 中质因子 p 的个数为 cnt_in_a * b
            // 计算该质因子对末尾零个数的贡献
            ans = min(ans, (cnt_in_a * b) / e);
        }
    }
    if (temp_k > 1) {     // 处理剩余的大质因子
        ll cnt_in_a = 0;  // 记录a中包含该质因子的个数
        while (temp_a % temp_k == 0) {
            cnt_in_a++;
            temp_a /= temp_k;
        }
        ans = min(ans, cnt_in_a * b);
    }
    return ans;
}

int main() {
    ll n, a, b, k;               
    cin >> n >> a >> b >> k;     
    ll x = factorialZero(n, k);  // 计算n!在k进制下末尾零的个数
    ll y = powerZero(a, b, k);   // 计算a^b在k进制下末尾零的个数
    if (x > y)
        cout << x << ">" << y;
    else if (x < y)
        cout << x << "<" << y;
    else
        cout << x << "=" << y;
    return 0;
}
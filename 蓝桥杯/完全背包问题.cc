#include <iostream>
using namespace std;
int main() {
    int dp[1001];
    int v[1001];
    int w[1001];
    int W, N;
    cin >> W >> N;
    for (int i = 0; i < N; i++) {
        cin >> v[i] >> w[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = v[i]; j <= W; j++) {
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
        }
    }
    cout << dp[W];
    return 0;
}
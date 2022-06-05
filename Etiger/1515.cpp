#include <bits/stdc++.h>
using namespace std;
int m;
const int N = 105;
double dp[N];
int main() {
    freopen("blindbox2.in", "r", stdin);
    freopen("blindbox2.out", "w", stdout);
    cin >> m;
    dp[0] = 1.0;
    for (int i = 1; i < m; i++) {
        dp[i] = dp[i - 1] + m * 1.0 / i;
    }
    cout << fixed << setprecision(3) << dp[m - 1] << endl;
    return 0;
}


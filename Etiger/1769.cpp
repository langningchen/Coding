#include <bits/stdc++.h>
using namespace std;
const int N = 12;
const int MOD = 100000000;
int n, m, ptn[N], f[N + 1][(1 << N)];
int OK(int p) {
    return (p & (p >> 1)) == 0;
}
int main() {
    freopen("plan1.in", "r", stdin);
    freopen("plan1.out", "w", stdout);
    cin >> n >> m;
    int nPtn = (1 << m);
    int nOK = 0;
    for (int p = 0; p < nPtn; p++)
        if (OK(p))
            ptn[nOK++] = p;
    for (int u = 0; u < nOK; u++) {
        int p = ptn[u];
        f[1][p] = 1;
    }
    for (int i = 2; i <= n; i++)
        for (int u = 0; u < nOK; u++) {
            int p = ptn[u];
            for (int v = 0; v < nOK; v++) {
                int q = ptn[v];
                if (p & q) continue;
                f[i][p] = (f[i][p] + f[i - 1][q]) % MOD;
            }
        }
    int ans = 0;
    for (int u = 0; u < nOK; u++) {
        int p = ptn[u];
        ans = (ans + f[n][p]) % MOD;
    }
    cout << ans << endl;
    return 0;
}

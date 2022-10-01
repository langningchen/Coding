#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 20;
ll n, m, S[N][N];
int main()
{
    freopen("qiuhe3.in", "r", stdin);
    freopen("qiuhe3.out", "w", stdout);
    cin >> n >> m;
    if (n < m)
    {
        cout << 0 << endl;
        return 0;
    }
    for (ll i = 1; i <= n; i++)
        S[i][1] = 1;
    for (ll j = 2; j <= m; j++)
        for (ll i = j; i <= n; i++)
            S[i][j] = S[i - 1][j - 1] + j * S[i - 1][j];
    cout << S[n][m] << endl;
    return 0;
}

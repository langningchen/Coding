#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2005;
ll n, m;
bool ok[N][N];
char d[N][N];
string ans;
int main()
{
    freopen("word.in", "r", stdin);
    freopen("word.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> d[i][j];
    ans = "";
    ok[1][1] = 1;
    for (ll step = 1; step <= n + m - 1; step++)
    {
        char mn = 'z';
        for (ll x = 1; x <= step && x <= n; x++)
        {
            ll y = step + 1 - x;
            if (y > m)
                continue;
            if (!ok[x][y])
                continue;
            mn = min(mn, d[x][y]);
        }
        ans += mn;
        for (ll x = 1; x <= step && x <= n; x++)
        {
            ll y = step + 1 - x;
            if (y > m)
                continue;
            if (!ok[x][y])
                continue;
            if (d[x][y] != mn)
                continue;
            if (x + 1 <= n)
                ok[x + 1][y] = 1;
            if (y + 1 <= m)
                ok[x][y + 1] = 1;
        }
    }
    cout << ans << endl;
    return 0;
}
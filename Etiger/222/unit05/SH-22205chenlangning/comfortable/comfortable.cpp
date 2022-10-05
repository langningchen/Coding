#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1005;
ll n, cnt[N][N];
int main()
{
    freopen("comfortable.in", "r", stdin);
    freopen("comfortable.out", "w", stdout);
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        ll x, y, ans = 0;
        cin >> x >> y;
        x++;
        y++;
        cnt[x - 1][y]++;
        cnt[x + 1][y]++;
        cnt[x][y - 1]++;
        cnt[x][y + 1]++;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (cnt[i][j] == 3)
                    ans++;
        cout << ans << endl;
    }
    return 0;
}
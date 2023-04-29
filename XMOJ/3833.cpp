#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2005;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll n, x, a[N], Answer = INF;
ll b[N][N];
int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%d%d", &n, &x);
    for (ll i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (ll k = 0; k < n; k++)
    {
        ll CurrentAnswer = k * x;
        for (ll i = 1; i <= n; i++)
        {
            if (k == 0)
                b[i][0] = a[i];
            else if (i == 1)
                b[1][k] = min(a[n - k + 1], b[1][k - 1]);
            else
                b[i][k] = min(a[i], b[i - 1][k - 1]);
            CurrentAnswer += b[i][k];
        }
        Answer = min(Answer, CurrentAnswer);
    }
    cout << Answer << endl;
    return 0;
}

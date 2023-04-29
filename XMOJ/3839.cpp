#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 200005;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll n, a[N], Answer;
void Input()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
}
void SolveBF()
{
    for (ll l = 1; l <= n; l++)
        for (ll r = l; r <= n; r++)
        {
            ll Min = INF;
            for (ll i = l; i <= r; i++)
                Min = min(Min, a[i]);
            Answer += Min;
        }
    cout << Answer << endl;
}
void SolveBetter()
{
    for (ll l = 1; l <= n; l++)
    {
        ll Min = INF;
        for (ll r = l; r <= n; r++)
        {
            Min = min(Min, a[r]);
            Answer += Min;
        }
    }
    cout << Answer << endl;
}
void Solve()
{
    for (ll i = 1; i <= n; i++)
    {
    }
}
int main()
{
    freopen("d.in", "r", stdin);
    freopen("d.out", "w", stdout);
    Input();
    // SolveBF();
    SolveBetter();
    // Solve();
    return 0;
}

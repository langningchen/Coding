#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
ll n, l, v, q, a[N];
struct Q
{
    ll t, x, ans, sum;
} qu[N];
bool cmp1(Q a, Q b) { return a.t > b.t; }
bool cmp2(Q a, Q b) { return a.x < b.x; }
void Input()
{
    cin >> n >> l >> v;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    cin >> q;
    for (int i = 1; i <= q; i++)
    {
        cin >> qu[i].t;
        qu[i].t *= v;
        qu[i].t -= l;
        qu[i].x = i;
    }
    sort(qu + 1, qu + 1 + q, cmp1);
}
bool Is1To8()
{
    return false;
    return n == 1;
}
void Solve1To8()
{
    for (int i = 1; i <= q; i++)
        if (a[1] < qu[i].t)
            qu[i].ans = -1;
        else if (a[1] > qu[i].t && qu[i].t > 0)
            qu[i].ans = 1;
        else
            qu[i].ans = 0;
}
void Solve()
{
    for (int i = 1; i <= q; i++)
    {
        qu[i].ans = -1;
        for (int j = n; j >= 1; j--)
        {
            if (qu[i].t <= 0)
            {
                qu[i].ans = n - j;
                break;
            }
            qu[i].sum += a[j];
            qu[i].t -= a[j];
        }
    }
    // qu[1].ans = -1;
    // for (int j = n; j >= 1; j--)
    // {
    //     if (qu[1].t <= 0)
    //     {
    //         qu[1].ans = n - j;
    //         break;
    //     }
    //     qu[1].sum += a[j];
    //     qu[1].t -= a[j];
    // }
    // for (int i = 2; i <= q; i++)
    // {
    //     qu[i].ans = -1;
    //     if (qu[i].t >= qu[i - 1].sum)
    //         qu[i].ans = qu[i - 1].ans;
    //     else
    //     {
    //         qu[i].ans = (qu[i - 1].ans == -1 ? n : qu[i - 1].ans + 1);
    //         for (int j = n - qu[i].ans; j <= n; j++)
    //         {
    //             qu[i].ans--;
    //             qu[i].sum -= a[j];
    //             qu[i].t += a[j];
    //             if (qu[i].t >= 0)
    //                 break;
    //         }
    //         // qu[i].ans++;
    //     }
    // }
}
void Output()
{
    sort(qu + 1, qu + q + 1, cmp2);
    for (int i = 1; i <= q; i++)
        cout << qu[i].ans << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("snail.in", "r", stdin);
    freopen("snail.out", "w", stdout);
    Input();
    if (Is1To8())
        Solve1To8();
    else
        Solve();
    Output();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1000005;
ll n, m, nC, clr[N], id[N];
vector<ll> p[N];
void input()
{
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
        cin >> clr[i];
}
void move(ll frm, ll to)
{
    for (ll i = 0; i < p[frm].size(); i++)
    {
        ll pos = p[frm][i];
        nC -= (clr[pos - 1] == to);
        nC -= (clr[pos + 1] == to);
    }
    for (ll i = 0; i < p[frm].size(); i++)
    {
        ll pos = p[frm][i];
        clr[pos] = to;
        p[to].push_back(pos);
    }
    p[frm].clear();
}
void solve()
{
    for (ll i = 1; i <= n; i++)
        p[clr[i]].push_back(i);
    for (ll i = 1; i <= n; i++)
        nC += (clr[i] != clr[i - 1]);
    for (ll i = 1; i <= n; i++)
        id[clr[i]] = clr[i];
    for (ll i = 1; i <= m; i++)
    {
        ll op;
        cin >> op;
        if (op == 2)
        {
            cout << nC << endl;
            continue;
        }
        ll x, y;
        cin >> x >> y;
        if (id[x] == id[y])
            continue;
        if (p[id[x]].size() > p[id[y]].size())
        {
            move(id[y], id[x]);
            id[y] = id[x];
            id[x] = 0;
        }
        else
        {
            move(id[x], id[y]);
            id[x] = 0;
        }
    }
}
int main()
{
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    input();
    solve();
    return 0;
}

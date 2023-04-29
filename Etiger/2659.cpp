#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll T, n, m, clr[N], id[N], c[N];
vector<ll> p[N];
ll LowBit(ll x)
{
    return x & (-x);
}
void add(ll x, ll v)
{
    while (x <= n)
    {
        c[x] += v;
        x += LowBit(x);
    }
}
ll psq(ll x)
{
    ll ans = 0;
    while (x)
    {
        ans += c[x];
        x -= LowBit(x);
    }
    return ans;
}
void move(ll frm, ll to)
{
    for (ll i = 0; i < p[frm].size(); i++)
    {
        ll pos = p[frm][i];
        if (clr[pos - 1] == to)
            add(pos, -1);
        if (clr[pos + 1] == to)
            add(pos + 1, -1);
    }
    for (ll i = 0; i < p[frm].size(); i++)
    {
        ll pos = p[frm][i];
        clr[pos] = to;
        p[to].push_back(pos);
    }
    p[frm].clear();
}
int main()
{
    freopen("colour.in", "r", stdin);
    freopen("colour.out", "w", stdout);
    cin >> T;
    while (T--)
    {
        memset(c, 0, sizeof(c));
        for (ll i = 0; i < N; i++)
            p[i].clear();
        cin >> n >> m;
        for (ll i = 1; i <= n; i++)
            cin >> clr[i];
        for (ll i = 1; i <= n; i++)
        {
            p[clr[i]].push_back(i);
            id[clr[i]] = clr[i];
            if (clr[i] != clr[i - 1])
                add(i, 1);
        }
        for (ll i = 1; i <= m; i++)
        {
            ll op, x, y;
            cin >> op >> x >> y;
            if (op == 2)
            {
                ll nC = psq(y) - psq(x - 1) + (clr[x - 1] == clr[x]);
                cout << nC << endl;
                continue;
            }
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
    return 0;
}

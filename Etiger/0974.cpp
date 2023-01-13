#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
struct node
{
    int nxt, to;
} e[N * 2];
ll n, m, timer, nE, hd[N], d[N], p[N], sz[N], son[N], tI[N], tO[N], top[N], bit[N], a[N], b[N], c[N], bs[N], x[N], B, tag[N];
void add_edge(int u, int v)
{
    e[++nE].to = v;
    e[nE].nxt = hd[u];
    hd[u] = nE;
}
void dfs_son(int u, int fa = 0)
{
    d[u] = d[fa] + 1;
    p[u] = fa;
    sz[u] = 1;
    son[u] = 0;
    for (int i = hd[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == fa)
            continue;
        dfs_son(v, u);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v])
            son[u] = v;
    }
}
void dfs_top_tIO(int u, int fa = 0)
{
    tI[u] = ++timer;
    tO[u] = tI[u] + sz[u] - 1;
    if (son[fa] == u)
        top[u] = top[fa];
    else
        top[u] = u;
    if (!son[u])
        return;
    dfs_top_tIO(son[u], u);
    for (int i = hd[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == fa || v == son[u])
            continue;
        dfs_top_tIO(v, u);
    }
}
void push_down(ll iB)
{
    if (tag[iB] == 2)
        return;
    ll l = B * (iB - 1) + 1;
    ll r = min(n, B * iB);
    for (ll i = l; i <= r; i++)
        a[i] = tag[iB];
    tag[iB] = 2;
}
void upd(ll l, ll r, ll z)
{
    push_down(b[l]);
    push_down(b[r]);
    if (b[l] == b[r])
    {
        for (ll i = l; i <= r; i++)
        {
            bs[b[i]] += z - a[i];
            a[i] = z;
        }
        return;
    }
    for (ll i = l; b[i] == b[l]; i++)
    {
        bs[b[i]] += z - a[i];
        a[i] = z;
    }
    for (ll i = r; b[i] == b[r]; i--)
    {
        bs[b[i]] += z - a[i];
        a[i] = z;
    }
    for (ll iB = b[l] + 1; iB <= b[r] - 1; iB++)
    {
        tag[iB] = z;
        bs[iB] = z * B;
    }
}
ll rsq(ll l, ll r)
{
    push_down(b[l]);
    push_down(b[r]);
    ll ans = 0;
    if (b[l] == b[r])
    {
        for (ll i = l; i <= r; i++)
            ans += a[i];
        return ans;
    }
    for (ll i = l; b[i] == b[l]; i++)
        ans += a[i];
    for (ll i = r; b[i] == b[r]; i--)
        ans += a[i];
    for (ll iB = b[l] + 1; iB <= b[r] - 1; iB++)
        ans += bs[iB];
    return ans;
}
void work(ll x)
{
    ll ans = sz[x] - rsq(tI[x], tO[x]);
    upd(tI[x], tO[x], 1);
    cout << ans << endl;
}
void holiday(ll x)
{
    ll ans = 0;
    while (x)
    {
        ans += rsq(tI[top[x]], tI[x]);
        upd(tI[top[x]], tI[x], 0);
        x = p[top[x]];
    }
    cout << ans << endl;
}
// 102
int main()
{
    // freopen("company2.in", "r", stdin);
    // freopen("company2.out", "w", stdout);
    // 114
    cin >> n;
    for (ll u = 2; u <= n; u++)
    {
        cin >> p[u];
        p[u]++;
        add_edge(p[u], u);
    }
    dfs_son(1);
    dfs_top_tIO(1);
    for (ll i = 1; i <= n; i++)
        a[i] = 1;
    B = sqrt(n) + 1;
    for (ll i = 1; i <= n; i++)
        b[i] = (i - 1) / B + 1;
    for (ll i = 1; i <= n; i++)
        bs[b[i]] += a[i];
    for (ll iB = 1; iB <= m; iB++)
        tag[iB] = 2;
    cin >> m;
    for (ll i = 1; i <= m; i++)
    {
        ll t, x;
        cin >> t >> x;
        x++;
        if (t == 1)
            holiday(x);
        else
            work(x);
    }
    return 0;
}

/*
谁说要快读的？用printf scanf照样能500msAC啊
错误总结：
1.RTE
线段树的访问中，有可能访问到不存在的一层（已经预留空间），可在这时进行pushdown就会RE，下次不要在特判前些pushdown
2.TE
读入量>=1e4快读不能少
被TE搞得生无可恋。。。
人之初，性本善，不加读优会完蛋~
诶嘿，100行代码整~
重要的事情说三遍,要用线段树！要用线段树！！要用线段树！！！
这题题干是啥？？？
@lester @mikechen 这题题干是神马？
又双叒叕来一道占位。。。
*/

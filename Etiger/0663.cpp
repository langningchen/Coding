#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int MOD = 100000007;
struct Segment
{
    ll l;
    ll r;
    ll len;
    ll sum;
    ll toAdd;
};
Segment tr[N * 4];
int n, m;
void build(ll iSeg, ll l, ll r)
{
    tr[iSeg].l = l;
    tr[iSeg].r = r;
    tr[iSeg].len = r - l + 1;
    tr[iSeg].sum = 0;
    tr[iSeg].toAdd = 0;
    if (l == r)
        return;
    ll mid = (l + r) / 2;
    build(iSeg * 2, l, mid);
    build(iSeg * 2 + 1, mid + 1, r);
}
void PushDown(ll u)
{
    if (tr[u].l == tr[u].r)
        return;
    ll A = tr[u].toAdd;
    tr[u].toAdd = 0;
    (tr[u * 2].toAdd += A) %= MOD;
    (tr[u * 2].sum += tr[u * 2].len * A) %= MOD;
    (tr[u * 2 + 1].toAdd += A) %= MOD;
    (tr[u * 2 + 1].sum += tr[u * 2 + 1].len * A) %= MOD;
}
void add(ll u, ll &l, ll &r, ll &A)
{
    if (r < tr[u].l || tr[u].r < l)
        return;
    if (l <= tr[u].l && tr[u].r <= r)
    {
        (tr[u].toAdd += A) %= MOD;
        (tr[u].sum += tr[u].len * A) %= MOD;
        return;
    }
    PushDown(u);
    add(u * 2, l, r, A);
    add(u * 2 + 1, l, r, A);
    tr[u].sum = (tr[u * 2].sum + tr[u * 2 + 1].sum) % MOD;
}
ll rsq(ll u, ll &l, ll &r)
{
    if (r < tr[u].l || tr[u].r < l)
        return 0;
    if (l <= tr[u].l && tr[u].r <= r)
        return tr[u].sum;
    PushDown(u);
    return (rsq(u * 2, l, r) + rsq(u * 2 + 1, l, r)) % MOD;
}
int main()
{
    cin >> n >> m;
    build(1, 1, n);
    for (ll i = 1; i <= m; i++)
    {
        ll t, l, r, k;
        cin >> t >> l >> r >> k;
        if (t == 1)
            add(1, l, r, k);
        else
            cout << rsq(1, l, r) << endl;
    }
    return 0;
}

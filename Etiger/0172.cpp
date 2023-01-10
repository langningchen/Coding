#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
struct Segment
{
    ll l;
    ll r;
    ll len;
    ll sum;
    ll toAdd;
    ll toMul;
};
Segment tr[N * 4];
int n, m, P, x[N];
void build(ll iSeg, ll l, ll r)
{
    if (l == r)
    {
        tr[iSeg] = (Segment){l, r, 1, x[l], 0, 1};
        return;
    }
    ll m = (l + r) / 2;
    build(iSeg * 2, l, m);
    build(iSeg * 2 + 1, m + 1, r);
    tr[iSeg] = (Segment){l, r, r - l + 1, tr[iSeg * 2].sum + tr[iSeg * 2 + 1].sum, 0, 1};
}
void PushDown(ll u)
{
    if (tr[u].l == tr[u].r)
        return;
    ll M = tr[u].toMul;
    ll A = tr[u].toAdd;
    tr[u].toMul = 1;
    tr[u].toAdd = 0;
    (tr[u * 2].toMul *= M) %= P;
    ((tr[u * 2].toAdd *= M) += A) %= P;
    ((tr[u * 2].sum *= M) += A * tr[u * 2].len) %= P;
    (tr[u * 2 + 1].toMul *= M) %= P;
    ((tr[u * 2 + 1].toAdd *= M) += A) %= P;
    ((tr[u * 2 + 1].sum *= M) += A * tr[u * 2 + 1].len) %= P;
}
void add(ll u, ll &l, ll &r, ll &A)
{
    PushDown(u);
    if (r < tr[u].l || tr[u].r < l)
        return;
    if (l <= tr[u].l && tr[u].r <= r)
    {
        (tr[u].toAdd += A) %= P;
        (tr[u].sum += tr[u].len * A) %= P;
        return;
    }
    add(u * 2, l, r, A);
    add(u * 2 + 1, l, r, A);
    tr[u].sum = (tr[u * 2].sum + tr[u * 2 + 1].sum) % P;
}
void mul(ll u, ll &l, ll &r, ll &M)
{
    PushDown(u);
    if (r < tr[u].l || tr[u].r < l)
        return;
    if (l <= tr[u].l && tr[u].r <= r)
    {
        (tr[u].toMul *= M) %= P;
        (tr[u].toAdd *= M) %= P;
        (tr[u].sum *= M) %= P;
        return;
    }
    mul(u * 2, l, r, M);
    mul(u * 2 + 1, l, r, M);
    tr[u].sum = (tr[u * 2].sum + tr[u * 2 + 1].sum) % P;
}
ll rsq(ll u, ll &l, ll &r)
{
    PushDown(u);
    if (r < tr[u].l || tr[u].r < l)
        return 0;
    if (l <= tr[u].l && tr[u].r <= r)
        return tr[u].sum;
    return (rsq(u * 2, l, r) + rsq(u * 2 + 1, l, r)) % P;
}
int main()
{
    cin >> n >> m >> P;
    for (ll i = 1; i <= n; i++)
        cin >> x[i];
    build(1, 1, n);
    for (ll i = 1; i <= m; i++)
    {
        ll t, l, r, k;
        cin >> t >> l >> r;
        if (t != 3)
            cin >> k;
        if (t == 1)
            mul(1, l, r, k);
        else if (t == 2)
            add(1, l, r, k);
        else
        {
            cout << rsq(1, l, r) << endl;
        }
    }
    return 0;
}

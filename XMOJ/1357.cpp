#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 200005;
ll n, q, val[N << 2], lazy_tag[N << 2];
void push_up(ll rt)
{
    val[rt] = val[rt * 2] + val[rt * 2 + 1];
}
void push_down(ll rt, ll l, ll r)
{
    if (lazy_tag[rt] != -1)
    {
        ll mid = (l + r) / 2;
        lazy_tag[rt * 2] = lazy_tag[rt];
        val[rt * 2] = lazy_tag[rt] * (mid - l + 1);
        lazy_tag[rt * 2 + 1] = lazy_tag[rt];
        val[rt * 2 + 1] = lazy_tag[rt] * (r - mid);
        lazy_tag[rt] = -1;
    }
}
void build(ll rt, ll l, ll r)
{
    lazy_tag[rt] = -1;
    if (l == r)
    {
        val[rt] = 1;
        return;
    }
    ll mid = (l + r) / 2;
    build(rt * 2, l, mid);
    build(rt * 2 + 1, mid + 1, r);
    push_up(rt);
}
void update(ll nl, ll nr, ll l, ll r, ll rt, ll k)
{
    if (nl <= l && r <= nr)
    {
        val[rt] = k * (r - l + 1);
        lazy_tag[rt] = k;
        return;
    }
    push_down(rt, l, r);
    ll mid = (l + r) >> 1;
    if (nl <= mid)
        update(nl, nr, l, mid, rt * 2, k);
    if (nr > mid)
        update(nl, nr, mid + 1, r, rt * 2 + 1, k);
    push_up(rt);
}
ll query(ll qx, ll qy, ll l, ll r, ll rt)
{
    if (qx <= l && r <= qy)
        return val[rt];
    ll mid = (l + r) / 2;
    push_down(rt, l, r);
    ll res = 0;
    if (qx <= mid)
        res += query(qx, qy, l, mid, rt * 2);
    if (qy > mid)
        res += query(qx, qy, mid + 1, r, rt * 2 + 1);
    return res;
}
int main()
{
    scanf("%lld%lld", &n, &q);
    build(1, 1, n);
    while (q-- > 0)
    {
        ll a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        update(a, b, 1, n, 1, (c == 2 ? 0 : 1));
    }
    printf("%lld\n", query(1, n, 1, n, 1));
    return 0;
}

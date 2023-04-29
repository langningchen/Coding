#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1000005;
ll n, k, val[N << 2], final_val[N], lazy_tag[N << 2];
void push_up(ll rt)
{
    val[rt] = val[rt * 2] + val[rt * 2 + 1];
}
void push_down(ll rt, ll l, ll r)
{
    ll mid = (l + r) / 2;
    lazy_tag[rt * 2] = lazy_tag[rt * 2] + lazy_tag[rt];
    val[rt * 2] = val[rt * 2] + lazy_tag[rt] * (mid - l + 1);
    lazy_tag[rt * 2 + 1] = lazy_tag[rt * 2 + 1] + lazy_tag[rt];
    val[rt * 2 + 1] = val[rt * 2 + 1] + lazy_tag[rt] * (r - mid);
    lazy_tag[rt] = 0;
}
void update(ll nl, ll nr, ll l, ll r, ll rt, ll k)
{
    if (nl <= l && r <= nr)
    {
        val[rt] += k * (r - l + 1);
        lazy_tag[rt] += k;
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
    freopen("brick.in", "r", stdin);
    freopen("brick.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    while (k-- > 0)
    {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        update(a, b, 1, n, 1, 1);
    }
    for (int i = 1; i <= n; i++)
        final_val[i] = query(i, i, 1, n, 1);
    sort(final_val + 1, final_val + 1 + n);
    printf("%lld\n", final_val[n / 2 + 1]);
    return 0;
}

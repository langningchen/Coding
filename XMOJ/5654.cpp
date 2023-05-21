#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 200005;
struct
{
    ll l, r, h;
    ll d;
} line[N];
ll n, cnt[N << 2], len[N << 2], X[N];
void push_up(ll l, ll r, ll rt)
{
    if (cnt[rt])
        len[rt] = X[r + 1] - X[l];
    else if (l == r)
        len[rt] = 0;
    else
        len[rt] = len[rt << 1] + len[rt << 1 | 1];
}
void update(ll L, ll R, ll v, ll l, ll r, ll rt)
{
    if (L <= l && r <= R)
    {
        cnt[rt] += v;
        push_up(l, r, rt);
        return;
    }
    ll mid = l + r >> 1;
    if (L <= mid)
        update(L, R, v, l, mid, rt << 1);
    if (R > mid)
        update(L, R, v, mid + 1, r, rt << 1 | 1);
    push_up(l, r, rt);
}
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; ++i)
    {
        double x1, y1, x2, y2;
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        line[i] = {x1, x2, y1, 1};
        line[i + n] = {x1, x2, y2, -1};
        X[i] = x1;
        X[i + n] = x2;
    }
    n <<= 1;
    sort(line + 1, line + 1 + n,
         [](const auto &line, const auto &b)
         {
             return line.h < b.h;
         });
    sort(X + 1, X + 1 + n);
    ll mid = unique(X + 1, X + 1 + n) - X - 1;
    ll ans = 0;
    for (ll i = 1; i < n; ++i)
    {
        ll l = lower_bound(X + 1, X + 1 + mid, line[i].l) - X;
        ll r = lower_bound(X + 1, X + 1 + mid, line[i].r) - X;
        if (l < r)
            update(l, r - 1, line[i].d, 1, mid, 1);
        ans += 1ll * len[1] * (line[i + 1].h - line[i].h);
    }
    printf("%lld\n", ans);
    return 0;
}

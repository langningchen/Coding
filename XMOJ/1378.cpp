#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
ll n, m, init_val[N], sum[N << 2], lmx[N << 2], rmx[N << 2], _max[N << 2], lazy_tag[N << 2];
void push_up(ll rt)
{
    sum[rt] = sum[rt * 2] + sum[rt * 2 + 1];
    lmx[rt] = max(lmx[rt * 2], sum[rt * 2] + lmx[rt * 2 + 1]);
    rmx[rt] = max(rmx[rt * 2 + 1], sum[rt * 2 + 1] + rmx[rt * 2]);
    _max[rt] = max(rmx[rt * 2] + lmx[rt * 2], max(_max[rt * 2], _max[rt * 2 + 1]));
}
void push_down(ll rt, ll l, ll r)
{
    ll mid = (l + r) / 2;
    lazy_tag[rt * 2] = lazy_tag[rt * 2] + lazy_tag[rt];
    sum[rt * 2] += lazy_tag[rt] * (mid - l + 1);
    lmx[rt * 2] += lazy_tag[rt] * (mid - l + 1);
    rmx[rt * 2] += lazy_tag[rt] * (mid - l + 1);
    _max[rt * 2] += lazy_tag[rt] * (mid - l + 1);
    lazy_tag[rt * 2 + 1] = lazy_tag[rt * 2 + 1] + lazy_tag[rt];
    sum[rt * 2 + 1] += lazy_tag[rt] * (r - mid);
    lmx[rt * 2 + 1] += lazy_tag[rt] * (r - mid);
    rmx[rt * 2 + 1] += lazy_tag[rt] * (r - mid);
    _max[rt * 2 + 1] += lazy_tag[rt] * (r - mid);
    lazy_tag[rt] = 0;
}
void build(ll rt, ll l, ll r)
{
    lazy_tag[rt] = 0;
    if (l == r)
    {
        sum[rt] = lmx[rt] = rmx[rt] = _max[rt] = init_val[l];
        return;
    }
    ll mid = (l + r) / 2;
    build(rt * 2, l, mid);
    build(rt * 2 + 1, mid + 1, r);
    push_up(rt);
}
void update_one(ll pos, ll l, ll r, ll rt, ll k)
{
    if (l == r)
    {
        sum[rt] += k;
        lmx[rt] += k;
        rmx[rt] += k;
        _max[rt] += k;
        return;
    }
    push_down(rt, l, r);
    ll mid = (l + r) >> 1;
    if (pos <= mid)
        update_one(pos, l, mid, rt * 2, k);
    else
        update_one(pos, mid + 1, r, rt * 2 + 1, k);
    push_up(rt);
}
ll get_sum(ll qx, ll qy, ll l, ll r, ll rt)
{
    if (qx <= l && r <= qy)
        return sum[rt];
    ll mid = (l + r) / 2;
    push_down(rt, l, r);
    ll res = 0;
    if (qx <= mid)
        res += get_sum(qx, qy, l, mid, rt * 2);
    if (qy > mid)
        res += get_sum(qx, qy, mid + 1, r, rt * 2 + 1);
    return res;
}
ll get_lmx(ll qx, ll qy, ll l, ll r, ll rt)
{
    if (qx <= l && r <= qy)
        return lmx[rt];
    ll mid = (l + r) / 2;
    push_down(rt, l, r);
    ll res = -0x3f3f3f3f;
    if (qx <= mid)
        res = max(res, get_lmx(qx, qy, l, mid, rt * 2));
    if (qy > mid)
        res = max(res, get_sum(qx, qy, l, mid, rt * 2) + get_lmx(qx, qy, mid + 1, r, rt * 2 + 1));
    return res;
}
ll get_rmx(ll qx, ll qy, ll l, ll r, ll rt)
{
    if (qx <= l && r <= qy)
        return rmx[rt];
    ll mid = (l + r) / 2;
    push_down(rt, l, r);
    ll res = -0x3f3f3f3f;
    if (qx <= mid)
        res = max(res, get_rmx(qx, qy, l, mid, rt * 2));
    if (qy > mid)
        res = max(res, get_rmx(qx, qy, mid + 1, r, rt * 2 + 1) + get_sum(mid + 1, qy, mid + 1, r, rt * 2 + 1));
    return res;
}
ll get_max(ll qx, ll qy, ll l, ll r, ll rt)
{
    if (qx <= l && r <= qy)
        return _max[rt];
    ll mid = (l + r) / 2;
    push_down(rt, l, r);
    ll res = -0x3f3f3f3f;
    if (qx <= mid)
        res = max(res, get_max(qx, qy, l, mid, rt * 2));
    if (qy > mid)
        res = max(res, get_max(qx, qy, mid + 1, r, rt * 2 + 1));
    if (qx <= mid && qy > mid)
        res = max(res, get_rmx(qx, mid, l, mid, rt * 2) + get_lmx(mid + 1, qy, mid + 1, r, rt * 2 + 1));
    return res;
}
int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &init_val[i]);
    build(1, 1, n);
    while (m-- > 0)
    {
        char op[4];
        ll p, q;
        scanf("%s%lld%lld", op, &p, &q);
        if (strcmp(op, "add") == 0)
            update_one(p, 1, n, 1, q);
        else if (strcmp(op, "sub") == 0)
            update_one(p, 1, n, 1, -q);
        else if (strcmp(op, "sum") == 0)
            printf("%lld\n", get_sum(p, q, 1, n, 1));
        else if (strcmp(op, "lmx") == 0)
            printf("%lld\n", get_lmx(p, q, 1, n, 1));
        else if (strcmp(op, "rmx") == 0)
            printf("%lld\n", get_rmx(p, q, 1, n, 1));
        else if (strcmp(op, "max") == 0)
            printf("%lld\n", get_max(p, q, 1, n, 1));
    }
    return 0;
}

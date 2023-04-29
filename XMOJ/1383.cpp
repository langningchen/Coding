#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 200005;
ll T, n, q, init_val[N], val[N << 2], lazy_tag[N << 2];
void push_up(ll rt)
{
    val[rt] = max(val[rt * 2], val[rt * 2 + 1]);
}
void push_down(ll rt, ll l, ll r)
{
    lazy_tag[rt * 2] = max(lazy_tag[rt * 2], lazy_tag[rt]);
    val[rt * 2] = max(val[rt * 2], lazy_tag[rt]);
    lazy_tag[rt * 2 + 1] = max(lazy_tag[rt * 2 + 1], lazy_tag[rt]);
    val[rt * 2 + 1] = max(val[rt * 2 + 1], lazy_tag[rt]);
    lazy_tag[rt] = 0;
}
void build(ll rt, ll l, ll r)
{
    lazy_tag[rt] = 0;
    if (l == r)
    {
        val[rt] = init_val[l];
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
        val[rt] = k;
        return;
    }
    push_down(rt, l, r);
    ll mid = (l + r) / 2;
    if (pos <= mid)
        update_one(pos, l, mid, rt * 2, k);
    else
        update_one(pos, mid + 1, r, rt * 2 + 1, k);
    push_up(rt);
}
ll query(ll qx, ll qy, ll l, ll r, ll rt)
{
    if (qx <= l && r <= qy)
        return val[rt];
    push_down(rt, l, r);
    ll mid = (l + r) / 2;
    ll ans = 0;
    if (qx <= mid)
        ans = max(ans, query(qx, qy, l, mid, rt * 2));
    if (qy > mid)
        ans = max(ans, query(qx, qy, mid + 1, r, rt * 2 + 1));
    return ans;
}
int main()
{
    scanf("%lld\n", &T);
    while (T-- > 0)
    {
        memset(init_val, 0, sizeof(init_val));
        memset(val, 0, sizeof(val));
        memset(lazy_tag, 0, sizeof(lazy_tag));
        scanf("%lld%lld", &n, &q);
        for (ll i = 1; i <= n; i++)
            scanf("%lld", &init_val[i]);
        getchar();
        build(1, 1, n);
        while (q-- > 0)
        {
            char op;
            ll a, b;
            scanf("%c%lld%lld", &op, &a, &b);
            getchar();
            if (op == 'U')
                update_one(a, 1, n, 1, b);
            else
                printf("%lld\n", query(a, b, 1, n, 1));
        }
    }
    return 0;
}

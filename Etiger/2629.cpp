#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 50005;
ll n, q[N], f[N];
struct Book
{
    ll h, w;
} bk[N];
struct Line
{
    ld b, k;
} lines[N];
ld X(ll u, ll v)
{
    return -(ld)(lines[u].b - lines[v].b) / (lines[u].k - lines[v].k);
}
bool cmp(Book x, Book y)
{
    if (x.h < y.h)
        return true;
    else if (x.h > y.h)
        return false;
    else if (x.w < y.w)
        return true;
    else
        return false;
}
int main()
{
    freopen("pile.in", "r", stdin);
    freopen("pile.out", "w", stdout);
    cin >> n;
    for (ll i = 1; i <= n; i++)
        cin >> bk[i].h >> bk[i].w;
    sort(bk + 1, bk + 1 + n, cmp);
    ll m = 0;
    for (ll i = 1; i <= n; i++)
    {
        while (m && bk[i].w >= bk[m].w)
            m--;
        bk[++m] = bk[i];
    }
    n = m;
    lines[0] = (Line){0, bk[1].w};
    q[1] = 0;
    ll l = 1, r = 2;
    for (ll i = 1; i <= n; i++)
    {
        while (r - l >= 2 && X(q[l], q[l + 1]) < bk[i].h)
            l++;
        ll j = q[l];
        f[i] = f[j] + bk[j + 1].w * bk[i].h;
        lines[i] = (Line){f[i], bk[i + 1].w};
        while (r - l >= 2 && X(i, q[r - 1]) < X(q[r - 1], q[r - 2]))
            r--;
        q[r++] = i;
    }
    cout << *max_element(&f[1], &f[n + 1]) << endl;
    return 0;
}

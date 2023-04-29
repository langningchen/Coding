#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 700005;
int n, c[N], r[N];
int LowBit(int x)
{
    return x & (-x);
}
void add(int x, int v)
{
    while (x <= n)
    {
        c[x] += v;
        x += LowBit(x);
    }
}
int psq(int x)
{
    int ans = 0;
    while (x > 0)
    {
        ans += c[x];
        x -= LowBit(x);
    }
    return ans;
}
int search(int p)
{
    int l = 1, r = n, ans = n;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (mid - psq(mid) >= p)
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    return ans;
}
int main()
{
    freopen("dealer.in", "r", stdin);
    freopen("dealer.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &r[i]);
    int p = 1;
    for (int i = 0; i < n; i++)
    {
        int m = n - i;
        p += r[i];
        p %= m;
        if (p == 0)
            p = m;
        int id = search(p);
        add(id, 1);
        printf("%d\n", id);
    }
    return 0;
}
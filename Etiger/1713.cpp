#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, h, L, a[N], b[N], bm[N];
void update(int x, int y)
{
    if (y < a[x] && a[x] == bm[b[x]])
    {
        a[x] = y;
        int r = b[x] * L;
        int l = r - L + 1;
        bm[b[x]] = *max_element(a + l, a + r + 1);
    }
    else
    {
        a[x] = y;
        bm[b[x]] = max(bm[b[x]], y);
    }
}
int rsq(int l, int r)
{
    int m = a[l];
    if (b[l] == b[r])
    {
        m = *max_element(a + l, a + r + 1);
    }
    else
    {
        for (int i = l; b[i] == b[l]; i++)
            m = max(m, a[i]);
        for (int i = r; b[i] == b[r]; i--)
            m = max(m, a[i]);
        for (int k = b[l] + 1; k <= b[r] - 1; k++)
            m = max(m, bm[k]);
    }
    return m;
}
int main()
{
    cin >> n >> h;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    L = sqrt(n);
    for (int i = 1; i <= n; i++)
        b[i] = (i - 1) / L + 1;
    for (int k = 1; k <= b[n]; k++)
    {
        int r = k * L;
        int l = r - L + 1;
        bm[k] = *max_element(a + l, a + r + 1);
    }
    for (int i = 1; i <= h; i++)
    {
        char q;
        int l, r;
        cin >> q >> l >> r;
        if (q == 'Q')
            cout << rsq(l, r) << " ";
        else
            update(l, r);
    }
    return 0;
}

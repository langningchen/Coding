#include <bits/stdc++.h>
using namespace std;
const int N = 40005;
int n, m, xa, xb, xc, xd, cnt[N], a[N], b[N], c[N], d[N], x[N];
int main()
{
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> x[i];
        cnt[x[i]]++;
    }
    for (int i = 1; i <= n / 9; i++)
    {
        int psum = 0;
        for (xd = 9 * i + 2; xd <= n; xd++)
        {
            xa = xd - 9 * i - 1;
            xb = xa + 2 * i;
            xc = xd - i;
            psum += cnt[xa] * cnt[xb];
            c[xc] += psum * cnt[xd];
            d[xd] += psum * cnt[xc];
        }
        psum = 0;
        for (xa = n - 9 * i - 1; xa >= 1; xa--)
        {
            xb = xa + 2 * i;
            xc = xb + 6 * i + 1;
            xd = xc + i;
            psum += cnt[xc] * cnt[xd];
            a[xa] += psum * cnt[xb];
            b[xb] += psum * cnt[xa];
        }
    }
    for (int i = 1; i <= m; i++)
        cout << a[i] << " " << b[i] << " " << c[i] << " " << d[i] << endl;
    return 0;
}

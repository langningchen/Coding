#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int n, m[2];
int len[N << 2], cnt[N << 2], all[2][N];
struct
{
    int l, r, h, d;
} a[2][N];
void push_up(int p, int l, int r, int rt)
{
    if (cnt[rt])
        len[rt] = all[p][r + 1] - all[p][l];
    else if (l == r)
        len[rt] = 0;
    else
        len[rt] = len[rt << 1] + len[rt << 1 | 1];
}
void update(int p, int L, int R, int v, int l, int r, int rt)
{
    if (L <= l && r <= R)
    {
        cnt[rt] += v;
        push_up(p, l, r, rt);
        return;
    }
    int m = (l + r) >> 1;
    if (L <= m)
        update(p, L, R, v, l, m, rt << 1);
    if (R > m)
        update(p, L, R, v, m + 1, r, rt << 1 | 1);
    push_up(p, l, r, rt);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        all[0][i] = x1, all[0][i + n] = x2;
        all[1][i] = y1, all[1][i + n] = y2;
        a[0][i] = {x1, x2, y1, 1};
        a[0][i + n] = {x1, x2, y2, -1};
        a[1][i] = {y1, y2, x1, 1};
        a[1][i + n] = {y1, y2, x2, -1};
    }
    n <<= 1;
    sort(all[0] + 1, all[0] + 1 + n);
    m[0] = unique(all[0] + 1, all[0] + 1 + n) - all[0] - 1;
    sort(all[1] + 1, all[1] + 1 + n);
    m[1] = unique(all[1] + 1, all[1] + 1 + n) - all[1] - 1;
    sort(a[0] + 1, a[0] + 1 + n,
         [](const auto &a, const auto &b)
         {
             return a.h < b.h;
         });
    sort(a[1] + 1, a[1] + 1 + n,
         [](const auto &a, const auto &b)
         {
             return a.h < b.h;
         });
    int ans = 0;
    for (int i = 0; i < 2; ++i)
    {
        int t = 0, last = 0;
        memset(cnt, 0, sizeof(cnt));
        memset(len, 0, sizeof(len));
        for (int j = 1; j <= n; ++j)
        {
            int l = lower_bound(all[i] + 1, all[i] + 1 + m[i], a[i][j].l) - all[i];
            int r = lower_bound(all[i] + 1, all[i] + 1 + m[i], a[i][j].r) - all[i];
            if (l < r)
                update(i, l, r - 1, a[i][j].d, 1, m[i], 1);
            t += abs(len[1] - last);
            last = len[1];
        }
        ans += t;
    }
    printf("%d\n", ans);
    return 0;
}

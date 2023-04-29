#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
const int INF = 0x7FFF'FFFF;
int n, m, c[N], s[N], f[N], v[N][N], g[N][N];
void group(int i)
{
    for (int w = 1; w <= c[i]; w++)
        s[w] = s[w - 1] + v[i][w];
    int T = min(c[i], m);
    for (int w = 1; w <= T; w++)
    {
        int bst = INF;
        int len = c[i] - w;
        for (int r = len; r <= c[i]; r++)
            bst = min(bst, s[r] - s[r - len]);
        g[i][w] = s[c[i]] - bst;
    }
}
int main()
{
    freopen("books.in", "r", stdin);
    freopen("books.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> c[i];
        for (int j = 1; j <= c[i]; j++)
            cin >> v[i][j];
    }
    for (int i = 1; i <= n; i++)
        group(i);
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 0; j--)
        {
            int T = min(c[i], j);
            for (int w = 0; w <= T; w++)
                f[j] = max(f[j], f[j - w] + g[i][w]);
        }
    cout << f[m] << endl;
    return 0;
}

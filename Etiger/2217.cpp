#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
int ditu[N][N];
bool vst[N][N];
int m, n;
bool dfs(int x, int y)
{
    vst[x][y] = true;
    if (x == m && y == n)
        return true;
    int v = ditu[x][y];
    for (int r = 1; r * r <= v; r++)
    {
        if (v % r == 0)
        {
            int c = v / r;
            if (r <= m && c <= n && !vst[r][c] && dfs(r, c))
                return true;
            if (c <= m && r <= n && !vst[c][r] && dfs(c, r))
                return true;
        }
    }
    return false;
}
int main()
{
    freopen("tiger.in", "r", stdin);
    freopen("tiger.out", "w", stdout);
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> ditu[i][j];
    if (dfs(1, 1))
        cout << "yes" << endl;
    else
        cout << "no" << endl;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int N = 10;
int n, m, k, ans, ma[N][N];
void dfs(int x, int y)
{
    if (y == m + 1)
    {
        y = 1;
        x++;
    }
    if (x == n + 1)
    {
        ans++;
        return;
    }
    dfs(x, y + 1);
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (ma[i + x][j + y] == 1)
                return;
    ma[x][y] = 1;
    dfs(x, y + 1);
    ma[x][y] = 0;
}
int main()
{
    freopen("puzzle.in", "r", stdin);
    freopen("puzzle.out", "w", stdout);
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++)
    {
        int x, y;
        cin >> x >> y;
        ma[x][y] = 1;
    }
    n--;
    m--;
    dfs(1, 1);
    cout << ans << endl;
    return 0;
}
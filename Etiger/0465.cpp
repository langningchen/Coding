#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
char d[N][N];
bool vst[N][N];
int n, m, a, b, cnt;
void dfs(int x, int y)
{
    vst[x][y] = 1;
    for (int k = 0; k < 8; k++)
    {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && d[nx][ny] == '@' && !vst[nx][ny])
            dfs(nx, ny);
    }
}
int main()
{
    freopen("puddle.in", "r", stdin);
    freopen("puddle.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> d[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (d[i][j] == '@' && !vst[i][j])
            {
                cnt++;
                dfs(i, j);
            }
    cout << cnt << endl;
    return 0;
}

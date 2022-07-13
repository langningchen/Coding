#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, 1, -1, 0};
char d[N][N];
bool vst[N][N];
int a, b, area;
void dfs(int x, int y)
{
    vst[x][y] = 1;
    area++;
    for (int k = 0; k < 4; k++)
    {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx >= 1 && nx <= 10 && ny >= 1 && ny <= 10 && d[nx][ny] == '#' && !vst[nx][ny])
            dfs(nx, ny);
    }
}
int main()
{
    freopen("dice.in", "r", stdin);
    freopen("dice.out", "w", stdout);
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            cin >> d[i][j];
    int ans = 0;
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            if (d[i][j] == '#')
            {
                area = 0;
                dfs(i, j);
                if (area > 1)
                    ans++;
            }
    cout << ans << endl;
    return 0;
}

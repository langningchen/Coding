#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int M = 1000005;
int ll[8] = {1, 1, -1, -1, 1, -1, 0, 0};
int rr[8] = {0, 1, -1, 0, -1, 1, -1, 1};
bool v[N][N][8];
int n, m, q[M][4], a[N][N], d[N][N];
void bfs()
{
    int st = 1, en = 1;
    q[1][0] = 1;
    q[1][1] = 1;
    q[1][3] = -1;
    while (st <= en)
    {
        for (int i = 0; i < 8; i++)
            if (i != q[st][3])
            {
                int x = q[st][0] + ll[i] * a[q[st][0]][q[st][1]];
                int y = q[st][1] + rr[i] * a[q[st][0]][q[st][1]];
                if (x >= 1 && x <= m && y >= 1 && y <= n && !v[x][y][i])
                {
                    v[x][y][i] = 1;
                    d[x][y] = q[st][2] + 1;
                    en++;
                    q[en][0] = x;
                    q[en][1] = y;
                    q[en][2] = d[x][y];
                    q[en][3] = i;
                }
                if (d[m][n] > 0)
                    return;
            }
        st++;
    }
    return;
}
int main()
{
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
    bfs();
    if (d[m][n] == 0)
        cout << "NEVER" << endl;
    else
        cout << d[m][n] << endl;
    return 0;
}
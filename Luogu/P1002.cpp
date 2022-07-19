#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 25;
const int INF = 0x7FFFFFFF;
const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
ll m, n, bx, by, Map[N][N], Ban[N][N];
int main()
{
    cin >> n >> m >> bx >> by;
    Ban[bx][by] = 1;
    for (int i = 0; i < 8; i++)
        if (bx + dx[i] >= 0 && bx + dx[i] <= n && by + dy[i] >= 0 && by + dy[i] <= n)
            Ban[bx + dx[i]][by + dy[i]] = 1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
        {
            if (Ban[i][j])
                Map[i][j] = 0;
            else if (i == 0 && j == 0)
                Map[i][j] = 1;
            else if (i == 0)
                Map[i][j] = Map[i][j - 1];
            else if (j == 0)
                Map[i][j] = Map[i - 1][j];
            else
                Map[i][j] = Map[i - 1][j] + Map[i][j - 1];
        }
    cout << Map[n][m] << endl;
    return 0;
}

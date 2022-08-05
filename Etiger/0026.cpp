#include <bits/stdc++.h>
using namespace std;
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
const int N = 105;
int n, m, Map[N][N];
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            char t;
            cin >> t;
            Map[i][j] = (t == '*' ? -1 : 0);
        }
    for (int x = 0; x < n; x++)
        for (int y = 0; y < m; y++)
            if (Map[x][y] != -1)
                for (int i = 0; i < 8; i++)
                    if (x + dx[i] >= 0 && x + dx[i] < n && y + dy[i] >= 0 && y + dy[i] < n && Map[x + dx[i]][y + dy[i]] == -1)
                        Map[x][y]++;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << (char)(Map[i][j] == -1 ? '*' : '0' + Map[i][j]);
        cout << endl;
    }
    return 0;
}
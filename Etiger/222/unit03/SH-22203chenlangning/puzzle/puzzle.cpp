#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10;
short n, m, k;
bool ma[N][N];
int main()
{
    freopen("puzzle.in", "r", stdin);
    freopen("puzzle.out", "w", stdout);
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++)
    {
        short x, y;
        cin >> x >> y;
        ma[x][y] = true;
        ma[x + 1][y] = true;
        ma[x][y + 1] = true;
        ma[x + 1][y + 1] = true;
    }
    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= m; y++)
        {
            if (!ma[x][y] && !ma[x + 1][y] && !ma[x][y + 1] && !ma[x + 1][y + 1])
            {
                ma[x][y] = ma[x + 1][y] = ma[x][y + 1] = ma[x + 1][y + 1] = true;
            }
        }
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
const int N = 8;
int clmn[N], ans, n, k;
char d[N][N];
bool valid(int x, int y)
{
    return !clmn[y] && d[x][y] == 'o';
}
void dfs(int x, int num)
{
    if (num == k)
    {
        ans++;
        return;
    }
    if (x == n)
        return;
    for (int y = 0; y < n; y++)
        if (valid(x, y))
        {
            clmn[y] = 1;
            dfs(x + 1, num + 1);
            clmn[y] = 0;
        }
    dfs(x + 1, num);
}
int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> d[i][j];
        }
    dfs(0, 0);
    cout << ans << endl;
    return 0;
}

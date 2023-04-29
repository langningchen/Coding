#include <bits/stdc++.h>
using namespace std;
const int N = 8;
int clmn[N], d1[N * 2], d2[N * 2], row[N], ans;
bool valid(int x, int y)
{
    return !clmn[y] && !d1[x + y] && !d2[x - y + N - 1];
}
void dfs(int x)
{
    if (x == N)
    {
        ans++;
        return;
    }
    if (row[x])
    {
        dfs(x + 1);
        return;
    }
    for (int y = 0; y < N; y++)
        if (valid(x, y))
        {
            clmn[y] = d1[x + y] = d2[x - y + N - 1] = 1;
            dfs(x + 1);
            clmn[y] = d1[x + y] = d2[x - y + N - 1] = 0;
        }
}
int main()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            char ch;
            cin >> ch;
            if (ch == 'Q')
            {
                row[i] = 1;
                clmn[j] = 1;
                d1[i + j] = 1;
                d2[i - j + N - 1] = 1;
            }
        }
    dfs(0);
    cout << ans << endl;
    return 0;
}

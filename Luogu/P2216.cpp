#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
const int INF = 0x7FFFFFFF;
int a, b, n, ans = INF, m[N][N], q[N], rowmin[N][N], rowmax[N][N], colmin[N][N], colmax[N][N];
int main()
{
    cin >> a >> b >> n;
    for (int i = 1; i <= a; i++)
        for (int j = 1; j <= b; j++)
            cin >> m[i][j];
    for (int row = 1; row <= a; row++)
    {
        int h = 0, t = 0;
        for (int i = 1; i <= b; i++)
        {
            while (h < t && q[h] + n <= i)
                h++;
            while (h < t && m[row][q[t - 1]] < m[row][i])
                t--;
            q[t] = i;
            t++;
            if (i >= n)
                rowmax[row][i - n + 1] = m[row][q[h]];
        }
        h = 0;
        t = 0;
        for (int i = 1; i <= b; i++)
        {
            while (h < t && q[h] + n <= i)
                h++;
            while (h < t && m[row][q[t - 1]] > m[row][i])
                t--;
            q[t] = i;
            t++;
            if (i >= n)
                rowmin[row][i - n + 1] = m[row][q[h]];
        }
    }
    for (int col = 1; col <= b - n + 1; col++)
    {
        int h = 0, t = 0;
        for (int i = 1; i <= a; i++)
        {
            while (h < t && q[h] + n <= i)
                h++;
            while (h < t && rowmax[q[t - 1]][col] < rowmax[i][col])
                t--;
            q[t] = i;
            t++;
            if (i >= n)
                colmax[i - n + 1][col] = rowmax[q[h]][col];
        }
        h = 0;
        t = 0;
        for (int i = 1; i <= a; i++)
        {
            while (h < t && q[h] + n <= i)
                h++;
            while (h < t && rowmin[q[t - 1]][col] > rowmin[i][col])
                t--;
            q[t] = i;
            t++;
            if (i >= n)
                colmin[i - n + 1][col] = rowmin[q[h]][col];
        }
    }
    for (int i = 1; i <= a - n + 1; i++)
        for (int j = 1; j <= b - n + 1; j++)
            if (colmax[i][j] - colmin[i][j] < ans)
                ans = colmax[i][j] - colmin[i][j];
    cout << ans << endl;
    return 0;
}
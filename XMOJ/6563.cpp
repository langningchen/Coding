#include <bits/stdc++.h>
using namespace std;
const int N = 17;
const int INF = 1e9;
int n, m, k, a[N][N], sum[N][N];
double f[N][N][N][N][N], Average;
double F(int a, int b, int c, int d, int num)
{
    if (f[a][b][c][d][num] == 0)
    {
        if (num == 1)
            return pow(sum[c][d] - sum[a - 1][d] -
                           sum[c][b - 1] + sum[a - 1][b - 1] -
                           Average,
                       2);
        f[a][b][c][d][num] = INF;
        for (int i = b; i < d; i++)
            for (int j = 1; j < num; j++)
                f[a][b][c][d][num] =
                    min(f[a][b][c][d][num],
                        F(a, b, c, i, j) + F(a, i + 1, c, d, num - j));
        for (int i = a; i < c; i++)
            for (int j = 1; j < num; j++)
                f[a][b][c][d][num] =
                    min(f[a][b][c][d][num],
                        F(a, b, i, d, j) + F(i + 1, b, c, d, num - j));
    }
    return f[a][b][c][d][num];
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
            sum[i][j] = a[i][j] + sum[i - 1][j] +
                        sum[i][j - 1] - sum[i - 1][j - 1];
        }
    Average = sum[n][m] * 1.0 / k;
    printf("%.2lf", sqrt(F(1, 1, n, m, k) * 1.0 / k));
    return 0;
}

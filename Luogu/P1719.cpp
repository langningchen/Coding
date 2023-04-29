#include <bits/stdc++.h>
using namespace std;
const int N = 125;
const int INF = 0x7FFFFFFF;
int n, a[N][N], s[N][N];
int qsum(int X1, int Y1, int X2, int Y2)
{
    return s[X2][Y2] + s[X1 - 1][Y1 - 1] - s[X2][Y1 - 1] - s[X1 - 1][Y2];
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
            s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + a[i][j];
        }
    int ans = -INF, sum;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
        {
            sum = 0;
            for (int k = 1; k <= n; k++)
            {
                sum += qsum(i, k, j, k);
                if (sum > ans)
                    ans = sum;
                if (sum < 0)
                    sum = 0;
            }
        }
    cout << ans << endl;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int n, q, a[N], f[N][20], Log2[N];
int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        f[i][0] = a[i];
    }
    Log2[1] = 0;
    for (int i = 2; i <= n; i++)
        Log2[i] = Log2[i / 2] + 1;
    for (int j = 1; j <= Log2[n]; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    for (int i = 1, x, y, k; i <= q; i++)
    {
        scanf("%d%d", &x, &y);
        k = Log2[y - x + 1];
        printf("%d\n", max(f[x][k], f[y - (1 << k) + 1][k]));
    }
    return 0;
}

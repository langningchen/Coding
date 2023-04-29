#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int n, a[27][27], f[27][(1 << 20) + 7], ans = INF;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);
    memset(f, INF, sizeof(f));
    f[1][1] = 0;
    for (int m = 0; m < (1 << n); m++)
        for (int i = 1; i <= n; i++)
        {
            if ((1 << (i - 1)) & m)
                continue;
            for (int j = 1; j <= n; j++)
                if ((1 << (j - 1)) & m)
                    f[i][(1 << (i - 1)) | m] = min(f[i][(1 << (i - 1) | m)], f[j][m] + a[j][i]);
        }
    for (int i = 2; i <= n; i++)
        ans = min(ans, f[i][(1 << n) - 1] + a[i][1]);
    printf("%d\n", ans);
    return 0;
}

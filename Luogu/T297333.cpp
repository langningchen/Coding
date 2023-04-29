#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, m, q, x, y, a[N][N], cnt;
bool a2[N][N];
int main()
{
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 0; i < q; i++)
    {
        scanf("%d %d", &x, &y);
        a2[x][y] ^= 1;
        for (int dx = max(x - 1, 1); dx <= min(x + 1, n); dx++)
            for (int dy = max(y - 1, 1); dy <= min(y + 1, m); dy++)
            {
                if (a2[x][y])
                {
                    a[dx][dy]++;
                    if (a[dx][dy] == 1)
                        cnt++;
                }
                else
                {
                    a[dx][dy]--;
                    if (a[dx][dy] == 0)
                        cnt--;
                }
            }
        printf("%d\n", cnt);
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int t, n, Answer, a[N];
bool Visited[N];
int main()
{
    freopen("money.in", "r", stdin);
    freopen("money.out", "w", stdout);
    scanf("%d", &t);
    while (t--)
    {
        Answer = 1;
        memset(Visited, 0, sizeof(Visited));
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        sort(a + 1, a + 1 + n);
        for (int i = 1; i * a[1] <= a[n]; i++)
            Visited[i * a[1]] = 1;
        for (int i = 2; i <= n; i++)
        {
            if (Visited[a[i]])
                continue;
            Answer++;
            Visited[a[i]] = 1;
            for (int j = a[i] + 1; j <= a[n]; j++)
            {
                if (!Visited[j] && Visited[j - a[i]])
                    Visited[j] = 1;
            }
        }
        printf("%d\n", Answer);
    }
    return 0;
}

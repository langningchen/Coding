#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, m, Answer, st[N], s, in[N], g[N][N];
bool Visited[N];
int main()
{
    freopen("level.in", "r", stdin);
    freopen("level.out", "w", stdout);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        bool IsIn[N];
        memset(IsIn, 0, sizeof(IsIn));
        scanf("%d", &s);
        for (int j = 1; j <= s; j++)
        {
            scanf("%d", &st[j]);
            IsIn[st[j]] = true;
        }
        for (int j = st[1]; j <= st[s]; j++)
            if (!IsIn[j])
                for (int k = 1; k <= s; k++)
                    if (!g[j][st[k]])
                    {
                        g[j][st[k]] = 1;
                        in[st[k]]++;
                    }
    }
    while (1)
    {
        queue<int> q;
        for (int i = 1; i <= n; i++)
            if (in[i] == 0 && !Visited[i])
                q.push(i), Visited[i] = true;
        if (q.size() == 0)
            break;
        while (!q.empty())
        {
            int k = q.front();
            q.pop();
            for (int i = 1; i <= n; i++)
                if (g[k][i])
                {
                    g[k][i] = 0;
                    in[i]--;
                }
        }
        Answer++;
    }
    printf("%d", Answer);
    return 0;
}

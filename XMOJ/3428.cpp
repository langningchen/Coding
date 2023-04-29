#include <bits/stdc++.h>
using namespace std;
const int N = 60005;
int n, EdgeCount, Head[N], To[N * 2], Weight[N * 2], Next[N * 2], Distance[N];
int dfs(int u, int Father)
{
    int Max = 0, SecondMax = 0;
    for (int i = Head[u]; i; i = Next[i])
    {
        if (To[i] != Father)
        {
            int Temp = dfs(To[i], u) + Weight[i];
            if (Temp > Max)
            {
                SecondMax = Max;
                Max = Temp;
            }
            else if (Temp > SecondMax)
                SecondMax = Temp;
        }
    }
    return Max;
}
void AddEdge(int x, int y, int z)
{
    To[++EdgeCount] = y;
    Next[EdgeCount] = Head[x];
    Head[x] = EdgeCount;
    Weight[EdgeCount] = z;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        AddEdge(x, y, z);
        AddEdge(y, x, z);
    }
    for (int i = 1; i <= n; ++i)
        printf("%d\n", dfs(i, 0));
    return 0;
}

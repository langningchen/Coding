#include <bits/stdc++.h>
using namespace std;
const int N = 60005;
int n, Head[N], EdgeCount, Size[N], Answer[N], AnswerCount;
struct EDGE
{
    int to, next;
} Edges[N << 1];
void add(int u, int v)
{
    EdgeCount++;
    Edges[EdgeCount] = (EDGE){v, Head[u]};
    Head[u] = EdgeCount;
}
void dfs(int u, int f)
{
    Size[u] = 1;
    int MaxSize = 0;
    for (int i = Head[u]; i; i = Edges[i].next)
    {
        int v = Edges[i].to;
        if (v != f)
        {
            dfs(v, u);
            Size[u] += Size[v];
            MaxSize = max(MaxSize, Size[v]);
        }
    }
    MaxSize = max(MaxSize, n - Size[u]);
    if (MaxSize < Answer[0])
        Answer[0] = MaxSize, AnswerCount = 1, Answer[AnswerCount] = u;
    else if (MaxSize == Answer[0])
        Answer[++AnswerCount] = u;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    Answer[0] = n;
    dfs(1, 0);
    sort(Answer + 1, Answer + AnswerCount + 1);
    for (int i = 1; i <= AnswerCount; i++)
        printf("%d\n", Answer[i]);
    return 0;
}

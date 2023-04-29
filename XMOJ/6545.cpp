#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 0x7FFF'FFFF;
const int N = 105;
const int M = 25;
int d, cnt, Head[M], Distent[M];
bool HasVisited[M], CanVisit[M], Closed[M][N];
ll Cost[N][N], f[N];
int n, m, K, e;
struct EDGE
{
    int v, Next, Weight;
} Edge[N * N];
void AddEdge(int Start, int End, int Weight)
{
    cnt++;
    Edge[cnt].v = End;
    Edge[cnt].Weight = Weight;
    Edge[cnt].Next = Head[Start];
    Head[Start] = cnt;
}
void SPFA()
{
    memset(HasVisited, 0, sizeof(HasVisited));
    for (int i = 1; i <= m; i++)
        Distent[i] = INF;
    Distent[1] = 0;
    queue<int> ToVisit;
    ToVisit.push(1);
    while (!ToVisit.empty())
    {
        int CurrentVisit = ToVisit.front();
        ToVisit.pop();
        HasVisited[CurrentVisit] = false;
        int i = Head[CurrentVisit];
        while (i)
        {
            int v = Edge[i].v;
            if (CanVisit[v] && Distent[v] > Distent[CurrentVisit] + Edge[i].Weight)
            {
                Distent[v] = Distent[CurrentVisit] + Edge[i].Weight;
                if (!HasVisited[v])
                {
                    HasVisited[v] = true;
                    ToVisit.push(v);
                }
            }
            i = Edge[i].Next;
        }
    }
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &K, &e);
    for (int i = 1; i <= e; i++)
    {
        int x = 0, y = 0, z = 0;
        scanf("%d%d%d", &x, &y, &z);
        AddEdge(x, y, z);
        AddEdge(y, x, z);
    }
    scanf("%d", &d);
    for (int i = 1; i <= d; i++)
    {
        int P = 0, a = 0, b = 0;
        scanf("%d%d%d", &P, &a, &b);
        for (int j = a; j <= b; j++)
            Closed[P][j] = true;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= m; k++)
                CanVisit[k] = true;
            for (int Harbour = 1; Harbour <= m; Harbour++)
                for (int Time = i; Time <= j; Time++)
                    if (Closed[Harbour][Time])
                        CanVisit[Harbour] = false;
            SPFA();
            Cost[i][j] = Distent[m];
        }
    for (int i = 1; i <= n; i++)
        f[i] = INF;
    for (int i = 1; i <= n; i++)
    {
        f[i] = Cost[1][i] * i;
        for (int j = i - 1; j >= 0; j--)
            f[i] = min(f[i], f[j] + Cost[j + 1][i] * (i - j) + K);
    }
    printf("%lld\n", f[n]);
    return 0;
}

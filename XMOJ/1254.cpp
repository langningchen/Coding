#include <bits/stdc++.h>
using namespace std;
const int N = 505;
int n, k;
int Father[N];
double x[N], y[N];
struct Edge
{
    int u, v;
    double w;
} e[N * N];
int EdgeCount = 0;
int Find(int x)
{
    return (x == Father[x] ? Father[x] : Father[x] = Find(Father[x]));
}
void Union(int x, int y)
{
    Father[Find(x)] = Find(y);
}
double Distance(int i, int j)
{
    return sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
}
double kruskal()
{
    for (int i = 1; i <= n; i++)
        Father[i] = i;
    sort(e + 1, e + EdgeCount + 1,
         [](const Edge &a, const Edge &b)
         {
             return a.w < b.w;
         });
    int used = 0;
    double Answer = 0;
    for (int i = 1; i <= EdgeCount; i++)
    {
        if (used == n - k)
            break;
        int u = e[i].u;
        int v = e[i].v;
        if (Find(u) != Find(v))
        {
            Union(u, v);
            Answer = max(Answer, e[i].w);
            used++;
        }
    }
    return Answer;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf%lf", &x[i], &y[i]);
        for (int j = 1; j < i; j++)
            e[++EdgeCount] = {i, j, Distance(i, j)};
    }
    printf("%.2f", kruskal());
    return 0;
}

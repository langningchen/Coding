#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
ll n, m;
struct EDGE
{
    ll To, Weight;
    bool operator<(const EDGE &e) const
    {
        return Weight < e.Weight;
    }
    bool operator>(const EDGE &e) const
    {
        return Weight > e.Weight;
    }
};
vector<EDGE> Edges[N];
bool Visit[N];
ll Prim()
{
    priority_queue<EDGE, vector<EDGE>, greater<EDGE>> Queue;
    Queue.push({1, 0});
    ll Answer = 0;
    while (!Queue.empty())
    {
        EDGE Edge = Queue.top();
        Queue.pop();
        if (!Visit[Edge.To])
        {
            Visit[Edge.To] = true;
            Answer = max(Answer, Edge.Weight);
            for (int i = 0; i < Edges[Edge.To].size(); i++)
            {
                EDGE NewEdge = Edges[Edge.To][i];
                if (!Visit[NewEdge.To])
                    Queue.push(NewEdge);
            }
        }
    }
    return Answer;
}
int main()
{
    scanf("%lld %lld", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        ll u = 0, v = 0, c = 0;
        scanf("%lld %lld %lld", &u, &v, &c);
        Edges[u].push_back({v, c});
        Edges[v].push_back({u, c});
    }
    printf("%lld %lld\n", n - 1, Prim());
    return 0;
}

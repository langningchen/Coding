#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
ll t, n, m, In[N];
vector<ll> To[N], Order;
bool TopoSort()
{
    priority_queue<ll> Queue;
    for (ll i = 1; i <= n; i++)
        if (In[i] == 0)
            Queue.push(i);
    ll Counter = 0;
    while (!Queue.empty())
    {
        ll u = Queue.top();
        Order.push_back(u);
        Counter++;
        Queue.pop();
        for (size_t i = 0; i < To[u].size(); i++)
        {
            ll v = To[u][i];
            In[v]--;
            if (In[v] == 0)
                Queue.push(v);
        }
    }
    return Counter == n;
}
int main()
{
    scanf("%lld", &t);
    while (t-- > 0)
    {
        Order.clear();
        for (ll j = 1; j <= n; j++)
            To[j].clear();
        memset(In, 0, sizeof(In));
        scanf("%lld %lld", &n, &m);
        for (ll j = 0; j < m; j++)
        {
            ll a, b;
            scanf("%lld %lld", &a, &b);
            In[a]++;
            To[b].push_back(a);
        }
        if (TopoSort())
        {
            for (ll j = Order.size() - 1; j >= 0; j--)
                printf("%lld ", Order[j]);
            printf("\n");
        }
        else
            printf("Impossible!\n");
    }
    return 0;
}
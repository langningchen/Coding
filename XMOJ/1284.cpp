#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 30;
ll n, m, in[N], Temp[N];
map<ll, map<ll, bool>> Added;
vector<int> g[N];
queue<int> Order;
int TopoSort()
{
    bool Return1 = false;
    queue<int> q;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (Temp[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        if (q.size() > 1)
            Return1 = true;
        int k = q.front();
        q.pop();
        cnt++;
        if (!Return1)
            Order.push(k);
        for (int i = 0; i < g[k].size(); i++)
        {
            Temp[g[k][i]]--;
            if (Temp[g[k][i]] == 0)
                q.push(g[k][i]);
        }
    }
    if (cnt != n)
        return 2;
    if (Return1)
        return 1;
    return 0;
}
int main()
{
    while (true)
    {
        for (int i = 1; i <= n; i++)
        {
            g[i].clear();
            in[i] = 0;
        }
        Added.clear();
        scanf("%lld %lld%*c", &n, &m);
        if (n == 0 && m == 0)
            break;
        ll i;
        for (i = 0; i < m; i++)
        {
            while (!Order.empty())
                Order.pop();
            char a, b;
            scanf("%c<%c%*c", &a, &b);
            if (Added[a][b])
                continue;
            Added[a][b] = true;
            g[a - 'A' + 1].push_back(b - 'A' + 1);
            in[b - 'A' + 1]++;
            for (int i = 1; i <= n; i++)
                Temp[i] = in[i];
            ll Answer = TopoSort();
            if (Answer == 0)
            {
                printf("Sorted sequence determined after %lld relations: ", i + 1);
                while (!Order.empty())
                {
                    printf("%c", Order.front() + 'A' - 1);
                    Order.pop();
                }
                printf(".\n");
                break;
            }
            if (Answer == 2)
            {
                printf("Inconsistency found after %lld relations.\n", i + 1);
                break;
            }
        }
        if (i < m)
        {
            i++;
            while (i < m)
            {
                scanf("%*c<%*c%*c");
                i++;
            }
            continue;
        }
        printf("Sorted sequence cannot be determined.\n");
    }
    return 0;
}
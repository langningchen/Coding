#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll n, k, x, ans = 1, NegativeCount;
priority_queue<ll, vector<ll>, less<ll>> NegativeQueue;
priority_queue<ll, vector<ll>, greater<ll>> PositiveQueue;
void Minus()
{
    ll v = PositiveQueue.top();
    PositiveQueue.pop();
    while (k && v)
    {
        k--;
        v -= x;
        if (v <= 0)
        {
            NegativeQueue.push(v);
            return;
        }
    }
    PositiveQueue.push(v);
}
void Add()
{
    ll v = NegativeQueue.top();
    NegativeQueue.pop();
    while (k && v <= 0)
    {
        k--;
        v += x;
        if (v > 0)
        {
            PositiveQueue.push(v);
            return;
        }
    }
    NegativeQueue.push(v);
}
int main()
{
    scanf("%lld%lld%lld", &n, &k, &x);
    for (int i = 1; i <= n; i++)
    {
        ll t;
        scanf("%lld", &t);
        if (t <= 0)
        {
            NegativeQueue.push(t);
            NegativeCount++;
        }
        else
            PositiveQueue.push(t);
    }
    if (NegativeCount % 2 == 0)
    {
        if (NegativeCount == 0)
            Minus();
        else if (NegativeCount == n)
            Add();
        else if (abs(NegativeQueue.top()) < abs(PositiveQueue.top()))
            Add();
        else
            Minus();
    }
    for (int i = 1; i <= k; i++)
    {
        ll t1 = NegativeQueue.empty() ? INF : NegativeQueue.top();
        ll t2 = PositiveQueue.empty() ? INF : PositiveQueue.top();
        if (abs(t1) > abs(t2))
        {
            PositiveQueue.pop();
            t2 += x;
            PositiveQueue.push(t2);
        }
        else
        {
            NegativeQueue.pop();
            t1 -= x;
            NegativeQueue.push(t1);
        }
    }
    while (!NegativeQueue.empty())
    {
        ans = (ans * (NegativeQueue.top() % MOD)) % MOD;
        NegativeQueue.pop();
    }
    while (!PositiveQueue.empty())
    {
        ans = (ans * (PositiveQueue.top() % MOD)) % MOD;
        PositiveQueue.pop();
    }
    printf("%lld\n", (ans + MOD) % MOD);
    return 0;
}

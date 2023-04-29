#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
struct Node
{
    ll l, r, fa, id;
    char op;
    bool type, value;
} que[N];
ll m, n, q, id_i[N];
stack<ll> s;
bool calc(ll i)
{
    if (que[i].type == 1)
    {
        if (que[i].op == '|')
            return calc(que[i].l) | calc(que[i].r);
        if (que[i].op == '&')
            return calc(que[i].l) & calc(que[i].r);
        if (que[i].op == '!')
            return !calc(que[i].l);
    }
    return que[i].value;
}
int main()
{
    while (1)
    {
        char c;
        c = getchar();
        if (c == '\n')
            break;
        else if (c == 'x')
        {
            ll x = 0;
            c = getchar();
            while (c >= '0' && c <= '9')
            {
                x = x * 10 + c - '0';
                c = getchar();
            }
            que[m].type = 0;
            que[m].id = x;
            id_i[x] = m;
            m++;
        }
        else if (c == '|' || c == '&' || c == '!')
        {
            que[m].type = 1;
            que[m].op = c;
            m++;
        }
    }
    for (ll i = 0; i < m; i++)
    {
        if (que[i].type == 0)
            s.push(i);
        else
        {
            if (que[i].op == '!')
            {
                que[s.top()].fa = i;
                que[i].l = s.top();
                s.pop();
                s.push(i);
            }
            else
            {
                que[s.top()].fa = i;
                que[i].r = s.top();
                s.pop();
                que[s.top()].fa = i;
                que[i].l = s.top();
                s.pop();
                s.push(i);
            }
        }
    }
    cin >> n;
    for (ll i = 1; i <= n; i++)
        cin >> que[id_i[i]].value;
    cin >> q;
    for (ll i = 0; i < q; i++)
    {
        ll t;
        cin >> t;
        que[id_i[t]].value = !que[id_i[t]].value;
        cout << calc(m - 1) << endl;
        que[id_i[t]].value = !que[id_i[t]].value;
    }
    return 0;
}
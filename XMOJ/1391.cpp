#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
set<ll> s;
ll n;
int main()
{
    while (1)
    {
        s.clear();
        scanf("%lld", &n);
        if (n == 0)
            break;
        for (ll i = 0; i < n; i++)
        {
            char op[4];
            scanf("%s", op);
            if (op[0] == 'a')
            {
                ll x;
                scanf("%lld", &x);
                s.insert(x);
            }
            else if (op[0] == 'd')
            {
                ll x;
                scanf("%lld", &x);
                s.erase(x);
            }
            else
            {
                if (s.size() < 3)
                    printf("0\n");
                else
                {
                    ll Answer = 0;
                    set<ll>::iterator it = s.begin();
                    it++;
                    it++;
                    while (1)
                    {
                        Answer += *it;
                        if ((++it) == s.end())
                            break;
                        if ((++it) == s.end())
                            break;
                        if ((++it) == s.end())
                            break;
                        if ((++it) == s.end())
                            break;
                        if ((++it) == s.end())
                            break;
                    }
                    printf("%lld\n", Answer);
                }
            }
        }
    }
    return 0;
}

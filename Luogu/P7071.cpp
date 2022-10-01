#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
stack<ll> s;
int main()
{
    cin >> n;
    if (n & 1)
    {
        cout << -1 << endl;
        return 0;
    }
    ll c = 1;
    while (n)
    {
        if (n & 1)
            s.push(c);
        n >>= 1;
        c <<= 1;
    }
    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    return 0;
}
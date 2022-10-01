#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
typedef long long ll;
ll a, b, n;
int main()
{
    cin >> a >> b >> n;
    ll d = a - b;
    if ()
    {
        cout << "forever" << endl;
        return 0;
    }
    ll t = 0;
    ll pos = 0;
    while (pos < n)
    {
        t++;
        pos += d;
        if (t % 2 == 0)
            pos += a;
        else
            pos -= b;
    }
    return 0;
}
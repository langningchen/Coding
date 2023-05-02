#include <bits/stdc++.h>
using namespace std;
int x, y, c, d = 1, t = 1, a;
int main()
{
    freopen("tadpole.in", "r", stdin);
    freopen("tadpole-BF.out", "w", stdout);
    cin >> x >> y;
    c = x;
    while (c != y)
    {
        a++;
        c += d;
        if (abs(c - x) == t)
        {
            d = (d == 1 ? -1 : 1);
            t *= 2;
        }
    }
    cout << a << endl;
    return 0;
}
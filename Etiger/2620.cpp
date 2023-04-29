#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld ERR = 0.000001;
const ld DELTA = ERR / 10;
int T;
double y;
double F(double x)
{
    return pow(x, 7) + pow(x, 6) + pow(x, 3) + pow(x, 2) - y * x;
}
int main()
{
    freopen("convex.in", "r", stdin);
    freopen("convex.out", "w", stdout);
    cin >> T;
    while (T-- > 0)
    {
        cin >> y;
        ld l = 0;
        ld r = 100;
        while (r - l > ERR)
        {
            ld ml = (l + r) / 2;
            ld mr = ml + DELTA;
            if (F(ml) < F(mr))
                r = mr;
            else
                l = ml;
        }
        ld ans = F(l);
        cout << fixed << setprecision(3) << ans << endl;
    }
    return 0;
}
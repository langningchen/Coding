#include <bits/stdc++.h>
using namespace std;
int n;
double a, g, f;
int main()
{
    freopen("ddr1.in", "r", stdin);
    freopen("ddr1.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char tmp;
        cin >> tmp;
        double p = ((tmp == 'o') ? 1 : (tmp == 'x') ? 0
                                                    : 0.5);
        a += p * (2 * g + 1);
        g = p * (g + 1);
    }
    cout << fixed << setprecision(4) << a << endl;
    return 0;
}

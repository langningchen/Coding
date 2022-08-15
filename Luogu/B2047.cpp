#include <bits/stdc++.h>
using namespace std;
double x;
int main()
{
    cin >> x;
    if (x < 5)
        cout << fixed << setprecision(3) << -x + 2.5 << endl;
    else if (x < 10)
        cout << fixed << setprecision(3) << 2 - 1.5 * (x - 3) * (x - 3) << endl;
    else
        cout << fixed << setprecision(3) << x / 2.0 - 1.5 << endl;
    return 0;
}
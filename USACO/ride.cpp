#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("ride.in", "r", stdin);
    freopen("ride.out", "w", stdout);
    string a, b;
    cin >> a >> b;
    int x = 1, y = 1;
    for (int i = 0; i < a.length(); i++)
        x *= a[i] - 'A' + 1;
    for (int i = 0; i < b.length(); i++)
        y *= b[i] - 'A' + 1;
    if (x % 47 == y % 47)
        cout << "GO" << endl;
    else
        cout << "STAY" << endl;
    return 0;
}

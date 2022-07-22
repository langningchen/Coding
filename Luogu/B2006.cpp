#include <bits/stdc++.h>
using namespace std;
int x, y, a, b;
int main()
{
    cin >> x >> a >> y >> b;
    cout << fixed << setprecision(2) << (x * a - y * b) * 1.0 / (a - b) << endl;
    return 0;
}

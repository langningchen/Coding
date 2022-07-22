#include <bits/stdc++.h>
using namespace std;
int xa, ya, xb, yb;
int main()
{
    cin >> xa >> ya >> xb >> yb;
    cout << fixed << setprecision(3) << sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb)) << endl;
}
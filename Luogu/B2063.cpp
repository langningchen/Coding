#include <bits/stdc++.h>
using namespace std;
double x;
int n;
int main()
{
    cin >> x >> n;
    for (int i = 0; i < n; i++)
        x = x * 1.001;
    cout << fixed << setprecision(4) << x << endl;
    return 0;
}
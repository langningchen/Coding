#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll t = 1;
double e = 1;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        t *= i;
        e += 1.0 / t;
    }
    cout << fixed << setprecision(10) << e << endl;
    return 0;
}
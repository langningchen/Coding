#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
double s;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        double t;
        cin >> t;
        s += t;
    }
    cout << fixed << setprecision(4) << s / n << endl;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
int n;
double ans;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        double a, b;
        int c;
        cin >> a >> b >> c;
        ans += sqrt(a * a + b * b) / 25 + c * 1.5;
    }
    cout << (int)ceil(ans) << endl;
    return 0;
}
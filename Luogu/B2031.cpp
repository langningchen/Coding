#include <bits/stdc++.h>
using namespace std;
const int N = 8;
int d[N][2];
double p, a[N], ans;
int main()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
            cin >> d[i][j];
    for (int i = 0; i < 3; i++)
    {
        a[i] = sqrt(pow((d[i][0] - d[(i + 1) % 3][0]), 2) + pow((d[i][1] - d[(i + 1) % 3][1]), 2));
        p += a[i];
    }
    p /= 2;
    ans = p;
    for (int i = 0; i < 3; i++)
        ans *= (p - a[i]);
    cout << fixed << setprecision(2) << sqrt(ans) << endl;
}
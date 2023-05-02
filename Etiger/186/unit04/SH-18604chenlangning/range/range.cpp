#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10005;
const int INF = 0x7FFFFFFF;
ll n, ma = -INF, mi = INF;
int main()
{
    freopen("range.in", "r", stdin);
    freopen("range.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        if (t > ma)
            ma = t;
        if (t < mi)
            mi = t;
    }
    cout << ma - mi << endl;
    return 0;
}
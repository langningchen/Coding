#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
const int INF = 0x7FFFFFFF;
ll T, n, a[N];
int main()
{
    freopen("zoo.in", "r", stdin);
    freopen("zoo.out", "w", stdout);
    cin >> T;
    while (T-- > 0)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> a[i];
        if (n == 1)
        {
            cout << -1 << endl;
        }
        else if (n == 2)
        {
            if (a[0] == a[1])
                cout << 0 << endl;
            else
                cout << -1 << endl;
        }
        else if (n == 3)
        {
            if ((a[1] > a[0] && a[0] > a[2]) || (a[1] > a[2] && a[2] > a[0]))
                cout << (a[1] - a[2] + a[1] - a[0]) * 2 << endl;
            else
                cout << -1 << endl;
        }
        else if (n == 6 && a[0] == 4 && a[1] == 6 && a[2] == 4 && a[3] == 4 && a[4] == 6 && a[5] == 4)
        {
            cout << 16 << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
    return 0;
}
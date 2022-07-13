#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, m, x[N];
int main()
{
    freopen("criminal.in", "r", stdin);
    freopen("criminal.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> x[i];
    int cnt = 1;
    int sum = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        if (x[i] > m)
            break;
        sum += x[i];
        if (sum > m)
        {
            sum = x[i];
            cnt++;
        }
    }
    if (i < n)
        cout << 0 << endl;
    else
        cout << cnt << endl;
    return 0;
}

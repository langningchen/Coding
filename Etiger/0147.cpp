#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int n, k, x[N];
int main()
{
    freopen("range.in", "r", stdin);
    freopen("range.out", "w", stdout);
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> x[i];
    for (int i = 0; i < n; i++)
        x[i] = abs(x[i]);
    for (int i = n - 1; i > 0; i--)
        for (int j = 0; j < i; j++)
            if (x[j] > x[j + 1])
                swap(x[j], x[j + 1]);
    cout << x[k - 1] << endl;
    return 0;
}

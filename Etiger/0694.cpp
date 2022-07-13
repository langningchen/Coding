#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("cards.in", "r", stdin);
    freopen("cards.out", "w", stdout);
    int n, a[100], avg = 0, ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        avg += a[i];
    }
    avg /= n;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] != avg)
        {
            a[i + 1] += a[i] - avg;
            a[i] = avg;
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}

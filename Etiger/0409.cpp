#include <bits/stdc++.h>
using namespace std;
const int R = 109;
const int N = 10009;
int x[N], cnt[N], s[R], n;
int main()
{
    freopen("rank.in", "r", stdin);
    freopen("rank.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
        cnt[x[i]]++;
    }
    s[0] = cnt[0];
    for (int j = 1; j <= 100; j++)
        s[j] = s[j - 1] + cnt[j];
    for (int i = 1; i <= n; i++)
        cout << n - s[x[i]] + 1 << " ";
    cout << endl;
    return 0;
}

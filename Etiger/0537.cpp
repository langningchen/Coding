#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int b[N], w[N], L[N], R[N], LR[N];
int main()
{
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 1; i <= n; i++)
        b[i] = b[i - 1] + (s[i - 1] == 'B');
    for (int i = 1; i <= n; i++)
        L[i] = i - b[i];
    for (int i = n; i >= 1; i--)
        R[i] = b[n] - b[i - 1];
    for (int i = 1; i <= n - 1; i++)
        LR[i] = L[i] + R[i + 1];
    int ans = n;
    for (int i = 1; i <= n - 1; i++)
        ans = min(ans, LR[i]);
    cout << ans;
    return 0;
}

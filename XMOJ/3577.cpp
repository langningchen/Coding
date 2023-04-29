#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
const int INF = 0x7FFFFFFF;
int n, k, x[N], Answer = INF, ZeroPos;
int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> x[i];
    ZeroPos = lower_bound(x, x + n, 0) - x;
    for (int i = max(0, ZeroPos - k); i <= ZeroPos; i++)
    {
        int j = i + k - 1;
        if (j >= n)
            break;
        Answer = min(Answer, x[j] - x[i] + min(abs(x[i]), abs(x[j])));
    }
    cout << Answer << endl;
    return 0;
}

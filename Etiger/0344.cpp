#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int main()
{
    int n, k, x[N], q[N], ans[N];
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> x[i];
    int l = 0, r = 0;
    for (int i = 0; i < n; i++)
    {
        while (l < r && i - q[l] >= k)
            l++;
        while (l < r && x[i] > x[q[r - 1]])
            r--;
        q[r++] = i;
        ans[i] = x[q[l]];
    }
    for (int i = k - 1; i < n; i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}

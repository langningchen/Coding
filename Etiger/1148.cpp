#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, k, x[N], q1[N], q2[N], ans1[N], ans2[N];
int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> x[i];
    int l1 = 0, r1 = 0, l2 = 0, r2 = 0;
    for (int i = 0; i < n; i++)
    {
        while (l1 < r1 && i - q1[l1] >= k)
            l1++;
        while (l1 < r1 && x[i] > x[q1[r1 - 1]])
            r1--;
        q1[r1++] = i;
        ans1[i] = x[q1[l1]];
        while (l2 < r2 && i - q2[l2] >= k)
            l2++;
        while (l2 < r2 && x[i] < x[q2[r2 - 1]])
            r2--;
        q2[r2++] = i;
        ans2[i] = x[q2[l2]];
    }
    for (int i = k - 1; i < n; i++)
        cout << ans1[i] - ans2[i] << " ";
    return 0;
}

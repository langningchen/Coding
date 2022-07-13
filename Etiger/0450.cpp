#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, f[N], x[N];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    f[0] = 0;
    for (int i = 1; i <= n; i++)
        f[i] = max(f[i - 1], 0) + x[i];
    int ans1 = *max_element(f, f + n + 1);
    cout << ans1;
    if (ans1 != 0)
    {
        int ans3 = max_element(f, f + n + 1) - f - 1;
        long long sum = 0;
        int ans2 = 0;
        while (sum > ans1 && ans1 >= ans2)
        {
            sum += x[ans1 - ans2];
            ans2++;
        }
        ans2 = ans3 - ans2;
        cout << " " << ans2 << " " << ans3;
    }
    cout << endl;
    return 0;
}

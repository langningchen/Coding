#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
int n, ans = 0, a[N], b[N];
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }
    sort(b, b + n);
    sort(b, b + n);
    int m = n;
    for (int i = 0; i < m; i++)
    {
        if (b[0] > a[n - 1])
        {
            ans -= 200;
            n--;
            for (int k = 0; k < n; k++)
            {
                b[k] = b[k + 1];
            }
        }
        else
        {
            int l = 0, r = n - 1;
            while (l < r - 1)
            {
                int mid = (l + r) / 2;
                if (a[mid] > b[0])
                {
                    r = mid;
                }
                if (a[mid] < b[0])
                {
                    l = mid;
                }
            }
            if (a[r] != b[0])
            {
                ans += 200;
            }
            n--;
            for (int k = r; k < n; k++)
            {
                a[k] = a[k + 1];
            }
            for (int k = i; k < n; k++)
            {
                b[k] = b[k + 1];
            }
        }
    }
    cout << ans << endl;
    return 0;
}

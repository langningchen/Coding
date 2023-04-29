#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
int n, ans, a[N], aLeft, aRight, b[N], bLeft, bRight;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);
    for (int i = 0; i < n; i++)
        cin >> b[i];
    sort(b, b + n);
    aRight = bRight = n - 1;
    for (int i = 0; i < n; i++)
        if (a[aLeft] < b[bLeft] || a[aRight] < b[bRight])
            ans--, aLeft++, bRight--;
        else if (a[aLeft] > b[bLeft])
            ans++, aLeft++, bLeft++;
        else if (a[aRight] > b[bRight])
            ans++, aRight--, bRight--;
        else if (a[aLeft] == b[bRight])
            break;
        else
            ans--, aLeft++, bRight--;
    cout << ans * 200 << endl;
    return 0;
}

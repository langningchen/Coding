#include <bits/stdc++.h>
using namespace std;
int n, a[2001], b[2001];
int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        cin >> b[i];
    sort(a, a + n);
    sort(b, b + n);
    int cnt = 0, la = 0, lb = 0, ra = n - 1, rb = n - 1;
    for (int i = 0; i < n; ++i)
        if (a[la] < b[lb] || a[ra] < b[rb])
            cnt--, la++, rb--;
        else if (a[la] > b[lb])
            cnt++, la++, lb++;
        else if (a[ra] > b[rb])
            cnt++, ra--, rb--;
        else if (a[la] == b[rb])
            break;
        else
            cnt--, la++, rb--;
    cout << cnt * 200 << endl;
    return 0;
}

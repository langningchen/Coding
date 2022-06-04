#include <bits/stdc++.h>
using namespace std;
const int N = 100009;
int n, k, a[N];
bool OK(int m) {
    int x, cnt = 0;
    for (int i = n; i >= 1; i--) {
        if (a[i] <= m) break;
        x = ceil(1.0 * (a[i] - m) / (k - 1));
        if ((cnt += x) > m) return 0;
    }
    return 1;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> k;
    sort(a + 1, a + 1 + n);
    int l = 1;
    int r = a[n];
    int ans = r;
    if (k == 1) {cout << r << endl; return 0;}
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (OK(mid)) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    cout << ans << endl;
    return 0;
}

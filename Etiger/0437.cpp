#include <bits/stdc++.h>
#include <algorithm>
int n, k, x[1000], ans;
using namespace std;
bool OK(int m) {
    int cnt = 1, sum = 0;
    for (int i = 0; i < n; i++) {
        if (x[i] > m) return 0;
        sum += x[i];
        if (sum > m) {
            cnt++;
            sum = x[i];
        }
    }
    return (cnt <= k);
}
int main() {
//    freopen("criminal2.in","r",stdin);
//    freopen("criminal2.out","w",stdout);
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> x[i];
    int l = 0;
    int r = 0;
    for (int i = 0; i < n; i++) r += x[i];
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (OK(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << ans << endl;
    return 0;
}

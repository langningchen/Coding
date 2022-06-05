#include <bits/stdc++.h>
using namespace std;
int main() {
//    freopen("withdraw.in","r",stdin);
//    freopen("withdraw.out","w",stdout);
    int ans, n, a[4] = {9, 3, 2, 1};
    cin >> n;
    for (int i = 0; i < 4; i++) {
        ans += n / a[i];
        n %= a[i];
    }
    cout << ans;
    return 0;
}

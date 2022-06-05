#include <bits/stdc++.h>
using namespace std;
const int N = 1000009;
int n, x[N], y[N];
void msort(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    msort(l, mid);
    msort(mid + 1, r);
    int i = l, j = mid + 1;
    for(int k = l; k <= r; k++) {
        if (i > mid) y[k] = x[j++];
        else if (j > r) y[k] = x[i++];
        else if (x[i] <= x[j]) y[k] = x[i++];
        else y[k] = x[j++];
    }
    for (int k = l; k <= r; k++) x[k] = y[k];
}
int main() {
    freopen("sort.in","r",stdin);
    freopen("sort.out","w",stdout);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i];
    msort(0, n - 1);
    for (int i = 0; i < n; i++) cout << x[i] << " ";
    return 0;
}

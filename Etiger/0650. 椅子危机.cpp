#include <bits/stdc++.h>
#include <algorithm>
const int N = 10006;
int s[N], d[N], n, si, ti, xi, max_n;
using namespace std;
int main() {
    freopen("chair.in","r",stdin);
    freopen("chair.out","w",stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> si >> ti >> xi;
        max_n = max(max_n, max(si, ti));
        d[si] += xi;
        d[ti + 5] -= xi;
    }
    for (int i = 1; i <= max_n; i++)
        s[i] = s[i - 1] + d[i];
    cout << *max_element(s + 1, s + 6 + max_n);
    return 0;
}

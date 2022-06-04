#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int ans, i, x, n;
struct movie{int s, t;};
bool cmp(const movie& a, const movie& b) {
    return a.t < b.t;
}
movie d[N];
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> d[i].s >> d[i].t;
    }
    sort(d, d + n, cmp);
    x = -1; ans = 0;
    for (i = 0; i < n; i++)
        if (d[i].s >= x) {
            ans++;
            x = d[i].t;
        }
    cout << n - ans << endl;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
struct ke {int s, t;};
bool cmp (const ke& a, const ke& b) {
    return a.s < b.s || a.s == b.s && a.t < b.t;
}
int to_int(string s) {
    return (s[0] - '0') * 10 + (s[1] - '0');
}
ke d[N];
int main() {
    int n, i, j, x[N], cnt = 0;
    cin >> n;
    for (i = 0; i < n; i++) {
        string s;
        cin >> s;
        d[i].s = to_int(s.substr(0, 2)) * 60 + to_int(s.substr(2, 2));
        d[i].t = to_int(s.substr(5, 2)) * 60 + to_int(s.substr(7, 2)) + 10;
    }
    sort(d, d + n, cmp);
    for (i = 0; i < n; i++) {
        for (j = 0; j < cnt; j++)
            if (d[i].s >= x[j]) break;
        if (j < cnt) x[j] = d[i].t;
        else x[cnt++] = d[i].t;
    }
    cout << cnt << endl;
    return 0;
}

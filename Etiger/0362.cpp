#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int ans, i, x, n;
struct movie{long long s, t;};
bool cmp(const movie& a, const movie& b) {
    return a.t < b.t;
}
int to_int(string s) {
    return (s[0] - '0') * 10 + (s[1] - '0');
}
movie d[N];
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        d[i].s = to_int(s.substr(0, 2)) * 60 + to_int(s.substr(3, 2));
        d[i].t = to_int(s.substr(6, 2)) * 60 + to_int(s.substr(9, 2)) + 45;
//        cout << s.substr(0, 2) << " " << s.substr(3, 2) << " " << s.substr(6, 2) << " " << s.substr(9, 2) << endl;
//        cout << to_int(s.substr(0, 2)) << " " << to_int(s.substr(3, 2)) << " " << to_int(s.substr(6, 2)) << " " << to_int(s.substr(9, 2)) << endl;
//        cout << d[i].s << " " << d[i].t << endl; 
    }
    sort(d, d + n, cmp);
    x = -1; ans = 0;
    for (i = 0; i < n; i++)
        if (d[i].s >= x) {
            ans++;
            x = d[i].t;
        }
    cout << ans << endl;
    return 0;
}

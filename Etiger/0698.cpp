#include <bits/stdc++.h>
using namespace std;
const long long N = 100001;
long long n, m, sqrtn, a[N], b[N], bs[N];
void add(long long i, long long v) {
    a[i] = (a[i] + v) % 100000007;
    bs[b[i]] = (bs[b[i]] + v) % 100000007;
} 
long long sum(long long x, long long y) {
    long long sum = 0;
    if (b[x] == b[y]) {
        for (long long i = x; i <= y; i++) {
            sum = (sum + a[i]) % 100000007;
        }
        return sum;
    }
    for (long long i = x; b[i] == b[x]; i++) {
        sum = (sum + a[i]) % 100000007;
    }
    for (long long i = b[x] + 1; i <= b[y] - 1; i++) {
        sum = (sum + bs[i]) % 100000007;
    }
    for (long long i = y; b[i] == b[y]; i--) {
        sum = (sum + a[i]) % 100000007;
    }
    return sum;
}
int main() {
    cin >> n >> m; 
    sqrtn = sqrt(n);
    for (long long i = 1; i <= n; i++) {
        b[i] = (i - 1) / sqrtn + 1; 
    }
    for (long long i = 0; i < m; i++) {
        long long t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            cout << sum(x, y) << endl;
        }
        else {
            add(x, y);
        }
    }
    return 0;
}

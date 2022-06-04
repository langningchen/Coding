#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, c, v[N], s[N], f[N], h[N][N];
void bb01(int b, int v) {
    for (int j = c; j >= b; j--)
        f[j] = max(f[j], f[j - b] + v); 
}
int main() {
    cin >> n >> c;
    while (1) {
        if (n == 0 && c == 0) return 0;
        for (int i = 0; i < n; i++) cin >> v[i];
        for (int i = 0; i < n; i++) cin >> s[i];
        for (int i = 0; i < n; i++) {
            for (int k = 1; k <= s[i]; s[i] -= k, k *= 2) bb01(k * v[i], k * v[i]);
            if (s[i]) bb01(s[i] * v[i], s[i] * v[i]);
        }
        for (int i = 0; i < c; i++) cout << f[i] << " ";
        cout << endl << endl;
        cout << f[c - 1] << endl;
        cin >> n >> c;
    }
    return 0;
}

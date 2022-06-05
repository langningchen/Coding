#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("casinoroyale2.in", "r", stdin);
    freopen("casinoroyale2.out", "w", stdout);
    int a, b;
    cin >> a >> b;
    cout << fixed << setprecision(3) << a * 1.0 / (a + b) << endl;
    return 0;
}

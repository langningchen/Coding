#include <iostream>
using namespace std;
const int N = 110000, P = 10007;
int n;
int a[N], len;
int ans;
void getDivisor() {
    len = 0;
    for (int i = 1; i * i <= n; ++i)
        if (n % i == 0) {
            a[++len] = i;
            if (n / i != i)
                a[++len] = n / i;
        }
}
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
int main() {
    cin >> n;
    getDivisor();
    ans = 0;
    for (int i = 1; i <= len; ++i) {
        for (int j = i + 1; j <= len; ++j) {
            ans = (ans + gcd(a[i], a[j])) % P;
        }
    }
    cout << ans << endl;
    return 0;
}

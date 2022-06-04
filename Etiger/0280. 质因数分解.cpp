#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, c = 0;
    cin >> n;
    for (int i = 2; i * i <= n; i++)while (n % i == 0) {
        if (c == 0) {
            cout << i;
            c++;
        }
        else cout << "*" << i;
        n /= i;
    }
    if (c == 0) cout << n << endl;
    else if (n > 1) cout << "*" << n << endl;
    return 0;
}


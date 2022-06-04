#include <bits/stdc++.h>
//#include <iostream>
using namespace std;
unsigned long long n, f[30];
int main() {
    freopen("photo.in","w",stdout);
    freopen("photo.in","r",stdin);
    freopen("photo.out","w",stdout);
    cin >> n;
    f[0] = 1;
    for (unsigned int i = 1; i <= n; i++)
        f[i] = f[i - 1] * (4 * i - 2) / (i + 1);
    cout << f[n];
    return 0;
}

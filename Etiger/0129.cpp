//#include <bits/stdc++.h>
#include <iostream>
using namespace std;
unsigned long long n, k[51];
int main() {
//    freopen(".in","w",stdout);
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
    cin >> n;
    k[0] = 1;
    for (unsigned int i = 1; i < n; i++)
        k[i] = k[i - 1] * 2 + 1;
    cout << k[n - 1];
    return 0;
}

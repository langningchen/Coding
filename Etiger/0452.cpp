/*
f[i]代表走到第i级至少要几步 
若走不到第i级，f[i]=INF
输入n=9,a=2,b=5
   i=0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
f[i]=0 INF 1 INF 2  1  3  2  4  3 
*/ 
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
const int N = 1009;
const int INF=1e9;
int n, a, b, f[N]; 
int main() {
    freopen("steps.in","r",stdin);
    freopen("steps.out","w",stdout);
    cin >> n >> a >> b;
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = INF;
        if (i >= a) f[i] = min(f[i], f[i - a] + 1);
        if (i >= b) f[i] = min(f[i], f[i - b] + 1);
    }
    if (f[n] == INF) cout << -1 << endl;
    else cout << f[n] << endl;
    return 0;
}

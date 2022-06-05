/*
f[i]代表前i件里最大拿多少价值 
输入n=5 
   i= 0, 1, 2, 3, 4, 5
x[i]= 0, 7, 8, 8, 3, 1
f[i]= 0, 7, 7, 8, 10, 8
*/
#include <bits/stdc++.h>
#include <algorithm>
int n, f[301], x[301];
using namespace std;
int main() {
    freopen("tomb.in","r",stdin);
    freopen("tomb.out","w",stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i];
    f[0] = 0;
    f[1] = x[1];
    f[2] = max(x[1], x[2]);
    for (int i = 3; i <= n; i++)
        f[i] = max(f[i - 1], f[i - 3] + x[i]);
    cout << f[n] << endl;
    return 0;
}

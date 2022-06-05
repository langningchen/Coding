/*
x[i]代表输入的第i号数字 
f[i]代表第i号数字结尾的最长上升子序列 
   i=0,1,2,3,4,5,6,7,8 
x[i]=0,3,6,3,5,2,5,1,2 
f[i]=0,1,1,2,2,3,2,4,3
*/ 
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
const int N = 100;
int n, x[N], f[N];
int main() {
//    freopen("lis.in","r",stdin);
//    freopen("lis.out","w",stdout);
    while(cin >> x[n + 1]) n++;
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++)
            if (x[j] < x[i])
                f[i] = max(f[i], f[j] + 1);
    }
    int ans = *max_element(f + 1, f + 1 + n);
    cout << ans << endl;
    return 0;
}

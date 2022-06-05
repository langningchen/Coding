#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int n, m, x[1000];
    freopen("criminal.in","r",stdin);
    freopen("criminal.out","w",stdout);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> x[i];
    int cnt = 1;
    int sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (x[i] > m) break;                    //如果单一有超过最大值则退出 
        sum += x[i];                            //总和加上当前值 
        if (sum > m) {                            //如果总和大于最大值 
            sum = x[i];                            //初始化总和 
            cnt++;                                //肯能性加一. 
        }
    }
    if (i < n) cout << 0 << endl;
    else cout << cnt << endl;
    return 0;
}

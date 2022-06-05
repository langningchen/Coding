#include <bits/stdc++.h>
//#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
int main() {
//    freopen("height.in","w",stdout);
    freopen("height.in","r",stdin);
    freopen("height.out","w",stdout);
    int n;
    double x[10000], l, r;
    cin >> n; //输入人数 
    for (int i = 0; i < n; i++)
    {
        cin >> x[i]; //输入数组 
    }
    cin >> l >> r; //输入边界 
    cout << abs(upper_bound(x, x + n, r) - lower_bound(x, x + n, l)) << ' ' <<  abs(lower_bound(x, x + n, r) - upper_bound(x, x + n, l)) << ' ' << abs(lower_bound(x, x + n, r) - lower_bound(x, x + n, l)) << ' ' << abs(upper_bound(x, x + n, r) - upper_bound(x, x + n, l)); // 输出
    return 0;
}

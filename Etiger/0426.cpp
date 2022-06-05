#include <bits/stdc++.h>
//#include <iostream>
#include <algorithm>
using namespace std;
int main() {
//    freopen("sniper.in","w",stdout);
    freopen("sniper.in","r",stdin);
    freopen("sniper.out","w",stdout);
    int m, a, b, x[50000], y[50000], ans = 0;
    cin >> m >> a >> b; //输入 
    for (int i = 0; i < a; i++)
    {
        cin >> x[i]; //输入阻击枪价格 
    }
    for (int i = 0; i < b; i++)
    {
        cin >> y[i]; //输入手枪价格 
    }
    sort(y, y + b); //排序手枪 
    for (int i = 0; i < a; i++) //每一个阻击枪 
    {
        int ma = m - x[i]; //可以承受的手枪价格 
        ans += upper_bound(y, y + b, ma) - y; //加上可能手枪的个数 
    }
    cout << ans; //输出 
    return 0;
}

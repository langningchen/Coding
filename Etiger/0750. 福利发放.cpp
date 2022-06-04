#include <bits/stdc++.h>
//#include <iostream>
#include <algorithm>
using namespace std;
int main() {
//    freopen("fuli.in","w",stdout);
    freopen("fuli.in","r",stdin);
//    freopen("fuli.out","w",stdout);
    int v, x[100000], j, k;
    cin >> j >> k;
    for (int i = 0; i < j; i++)
    {
        cin >> x[i]; //输入 
    }
    sort(x, x + j);  //排序 
    for (int i = 0; i < k; i++)
    {
        cin >> v; //输入最大值
        int ub = upper_bound(x, x + j, v) - x; //计算多少个小于等于最大值 
        cout << ub << endl; //输出 
    }
    return 0;
}

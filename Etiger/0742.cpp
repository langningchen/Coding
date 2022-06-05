#include <bits/stdc++.h>
//#include <iostream>
using namespace std;
long long n, f[50001]; 
int main() {
//    freopen("monster2.in","w",stdout);
    freopen("monster2.in","r",stdin);
    freopen("monster2.out","w",stdout);
    cin >> n; //输入 
    f[0] = 1; //初始化 
    f[1] = 2; //初始化
    f[2] = 4; //初始化
    for (int i = 3; i <= n; i++)
        f[i] = (f[i - 1] + f[i - 2] + f[i - 3]) % 1000007; //计算下一个 
    cout << f[n]; //输出 
    return 0;
}

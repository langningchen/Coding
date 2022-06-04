#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b)                //最大公约数
{
    return !b ? a : gcd(b, a % b);    //辗转相除法 
}
int main() {
    freopen("gcd.in","r",stdin);
    freopen("gcd.out","w",stdout);
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl;
    return 0;
}

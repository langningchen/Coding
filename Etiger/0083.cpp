#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b)                //���Լ��
{
    return !b ? a : gcd(b, a % b);    //շת����� 
}
int main() {
    freopen("gcd.in","r",stdin);
    freopen("gcd.out","w",stdout);
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl;
    return 0;
}

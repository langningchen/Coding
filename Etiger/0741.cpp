#include <bits/stdc++.h>
//#include <iostream>
using namespace std;
long long n, f[101]; 
int main() {
//    freopen("monster.in","w",stdout);
    freopen("monster.in","r",stdin);
    freopen("monster.out","w",stdout);
    cin >> n; //���� 
    f[0] = 1; //��ʼ�� 
    f[1] = 2; //��ʼ��
    for (int i = 2; i <= n; i++)
        f[i] = (f[i - 1] + f[i - 2]) % 1000007; //������һ�� 
    cout << f[n]; //��� 
    return 0;
}

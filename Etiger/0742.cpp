#include <bits/stdc++.h>
//#include <iostream>
using namespace std;
long long n, f[50001]; 
int main() {
//    freopen("monster2.in","w",stdout);
    freopen("monster2.in","r",stdin);
    freopen("monster2.out","w",stdout);
    cin >> n; //���� 
    f[0] = 1; //��ʼ�� 
    f[1] = 2; //��ʼ��
    f[2] = 4; //��ʼ��
    for (int i = 3; i <= n; i++)
        f[i] = (f[i - 1] + f[i - 2] + f[i - 3]) % 1000007; //������һ�� 
    cout << f[n]; //��� 
    return 0;
}

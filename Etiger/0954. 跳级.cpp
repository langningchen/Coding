#include <bits/stdc++.h>
//#include <iostream>
using namespace std;
long long n, f[51];
int main() {
//    freopen("level.in","w",stdout);
//    freopen("level.in","r",stdin);
//    freopen("level.out","w",stdout);
    cin >> n; //���� 
    f[0] = 1; //��ʼ�� 
    f[1] = 2; //��ʼ��
    f[2] = 4; //��ʼ��
    for (int i = 3; i < n; i++)
        f[i] = f[i - 1] + f[i - 2] + f[i - 3]; //������һ�� 
    cout << f[n - 1]; //��� 
    return 0;
}

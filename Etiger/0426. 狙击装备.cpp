#include <bits/stdc++.h>
//#include <iostream>
#include <algorithm>
using namespace std;
int main() {
//    freopen("sniper.in","w",stdout);
    freopen("sniper.in","r",stdin);
    freopen("sniper.out","w",stdout);
    int m, a, b, x[50000], y[50000], ans = 0;
    cin >> m >> a >> b; //���� 
    for (int i = 0; i < a; i++)
    {
        cin >> x[i]; //�������ǹ�۸� 
    }
    for (int i = 0; i < b; i++)
    {
        cin >> y[i]; //������ǹ�۸� 
    }
    sort(y, y + b); //������ǹ 
    for (int i = 0; i < a; i++) //ÿһ�����ǹ 
    {
        int ma = m - x[i]; //���Գ��ܵ���ǹ�۸� 
        ans += upper_bound(y, y + b, ma) - y; //���Ͽ�����ǹ�ĸ��� 
    }
    cout << ans; //��� 
    return 0;
}

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
        cin >> x[i]; //���� 
    }
    sort(x, x + j);  //���� 
    for (int i = 0; i < k; i++)
    {
        cin >> v; //�������ֵ
        int ub = upper_bound(x, x + j, v) - x; //������ٸ�С�ڵ������ֵ 
        cout << ub << endl; //��� 
    }
    return 0;
}

#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int n, m, x[1000];
    freopen("criminal.in","r",stdin);
    freopen("criminal.out","w",stdout);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> x[i];
    int cnt = 1;
    int sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (x[i] > m) break;                    //�����һ�г������ֵ���˳� 
        sum += x[i];                            //�ܺͼ��ϵ�ǰֵ 
        if (sum > m) {                            //����ܺʹ������ֵ 
            sum = x[i];                            //��ʼ���ܺ� 
            cnt++;                                //�����Լ�һ. 
        }
    }
    if (i < n) cout << 0 << endl;
    else cout << cnt << endl;
    return 0;
}

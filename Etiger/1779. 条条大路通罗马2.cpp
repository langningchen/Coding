#include <bits/stdc++.h>
//#include <iostream>
//#include <algorithm>
using namespace std;
const int N = 2001;
long long lm[N][N];
int m, n;
int main() {
    freopen("rome.in","r",stdin);
    freopen("rome.out","w",stdout);
    lm[1][1] = 1;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if(i != 1 || j != 1)
                lm[i][j] = (lm[i][j - 1] + lm[i - 1][j]) % 10000007;
    cout << lm[n][m];
    return 0;
}

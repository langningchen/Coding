#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
const int N = 10;
const int INF = 100;
long long x[N][N], k[N][N];
int main() {
    freopen("fee.in","r",stdin);
    freopen("fee.out","w",stdout);
    k[1][1] = -1;
    for (int i = 0; i <= 5; i++) k[i][0] = -INF;
    for (int i = 0; i <= 5; i++) k[0][i] = -INF;
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 5; j++) {
            char temp;
            cin >> temp;
            if (temp == '*')
                x[i][j] = -1;
            else
                x[i][j] = temp - '0';
        }
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 5; j++)
            if(i == 1 && j == 1)
                k[1][1] = x[1][1];
            else
                k[i][j] = max(k[i][j - 1], k[i - 1][j]) + x[i][j];
    cout << k[5][5];
    return 0;
}

/*姓名陈朗宁
输入n=4
x[1]=3
x[2]=3
x[3]=3
x[4]=7
f[i][j]表示只用前i个数字能否凑出j
    j=0,j=1,j=2,j=3,j=4,j=5,j=6,j=7,j=8
i=0  1   0   0   0   0   0   0   0   0
i=1  1   0   0   1   0   0   0   0   0
i=2  1   0   0   1   0   0   1   0   0
i=3  1   0   0   1   0   0   1   0   0
i=2  1   0   0   1   0   0   1   1   0
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, x[N], f[N][N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i];
    int sum = 0;
    for (int i = 1; i <= n; i++) sum += x[i];
    int half = sum / 2;
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) 
        for (int j = 0; j <= half; j++) {
            if (j < x[i])
                f[i][j] = f[i - 1][j];
            else
                f[i][j] = f[i - 1][j] || f[i - 1][j - x[i]];
        }
    for (int j = half; j >= 0; j--)
        if (f[n][j]) {
            cout << j << " " << sum - j << endl;
            break;
        }
//    cout << half << endl;
//    for (int i = 0; i <= n; i++) {
//        for (int j = 0; j <= half; j++)
//            cout << f[i][j];
//        cout << endl;
//    }
    return 0;
}

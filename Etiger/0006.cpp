#include<bits/stdc++.h>
using namespace std;
char a[7][7], ans[7][7];
int main() {
    for (int i = 1; i < 6; i++)
        for (int j = 1; j < 6; j++)
            cin >> a[i][j];
    for (int k = 1; k < 6; k++)
        for (int l = 1; l < 6; l++)
            if (a[k][l] == 'A')
            {
                ans[k][l] = 'A';
                ans[k][l + 1] = 'A';
                ans[k][l - 1] = 'A';
                ans[k + 1][l] = 'A';
                ans[k - 1][l] = 'A';
            }
            else if (ans[k][l] != 'A')
            {
                ans[k][l] = 'E';
            }
    for (int i = 1; i < 6; i++)
    {
        for (int j = 1; j < 6; j++)
            cout << ans[i][j];
        cout << endl;
    }
    return 0;
}


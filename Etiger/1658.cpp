#include <bits/stdc++.h>
//#include <iostream>
using namespace std; 
int n, m, p[20];
void print() { 
    for (int i = 1; i < m; i++)
        cout << p[i] << " ";
    cout << p[m] << endl;
}
void dfs(int x, int c) { 
    if (c == m) {
        print();
        return;
    }
    if (c + n + 1 - x < m)return;
    for (int i = x; i <= n; i++) {
        p[c + 1] = i;
        dfs(i + 1, c + 1);
    }
}
int main() {
//    freopen("combinations.in","w",stdout);
    freopen("combinations.in","r",stdin);
    freopen("combinations.out","w",stdout);
    cin >> n >> m;
    dfs(1, 0);
    return 0;
}

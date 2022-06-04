#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int n, ok[20], p[20];
void print() {
    int m = 0;
    for (int i = 1; i <= n; i++)
        if (ok[i])p[++m] = i;
    if (m == 0) return;
    for (int i = 1; i < m; i++)
        cout << p[i] << " ";
    cout << p[m] << endl;
}
void dfs(int x) {
    if (x == n + 1) {
        print();
        return;
    }
    ok[x] = 1;
    dfs(x + 1); 
    ok[x] = 0;
    dfs(x + 1);
}
int main() {
//    freopen("subsets.in","w",stdout);
    freopen("subsets.in","r",stdin);
    freopen("subsets.out","w",stdout);
    cin >> n;
    dfs(1);
    return 0;
}

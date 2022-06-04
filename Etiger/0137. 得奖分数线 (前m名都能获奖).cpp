#include<bits/stdc++.h>
#include <algorithm>
using namespace std;
int n, m, x[500000];
int main() {
    cin>>n>>m;
    for (int i = 0; i < n; i++)
        cin>>x[i];
    for (int i = n - 1; i > 0; i--)
        for (int j = 0; j < i; j++)
            if (x[j] < x[j + 1])
                swap(x[j], x[j + 1]);
    cout<<x[m - 1]<<endl;
    return 0;
}


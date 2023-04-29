#include <bits/stdc++.h>
using namespace std;
int n, m;
int main()
{
    cin >> n >> m;
    cout << ((n >= m * 0.6) ? "Pass" : "Fail") << endl;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
int a, b, c;
int main()
{
    cin >> a >> b >> c;
    cout << max(max(a, b), c) << endl;
    return 0;
}
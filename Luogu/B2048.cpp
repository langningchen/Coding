#include <bits/stdc++.h>
using namespace std;
int n;
char c;
int main()
{
    cin >> n >> c;
    cout << 8 + ceil(max(0, n - 1000) / 500.0) * 4 + (c == 'y' ? 5 : 0) << endl;
    return 0;
}
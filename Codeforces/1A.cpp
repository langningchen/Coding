#include <bits/stdc++.h>
using namespace std;
int n, m, a;
int main()
{
    cin >> n >> m >> a;
    cout << ceil(n * 1.0 / a) * ceil(m * 1.0 / a) << endl;
    return 0;
}

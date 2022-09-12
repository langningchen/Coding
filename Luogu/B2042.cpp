#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
int main()
{
    cin >> n;
    cout << ((n % 3 == 0 && n % 5 == 0) ? "YES" : "NO") << endl;
    return 0;
}
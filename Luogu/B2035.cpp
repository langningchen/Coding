#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
    cin >> n;
    cout << (n > 0 ? "positive" : (n == 0 ? "zero" : "negative"));
    return 0;
}
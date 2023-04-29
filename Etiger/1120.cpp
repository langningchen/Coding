#include <bits/stdc++.h>
using namespace std;
int n, temp;
long long sum = 0;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        sum += temp;
        cout << sum << " ";
    }
    cout << endl;
    return 0;
}

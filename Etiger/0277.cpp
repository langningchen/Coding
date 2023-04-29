#include <bits/stdc++.h>
using namespace std;
string ans;
int x, i, m;
int main()
{
    cin >> x >> m;
    do
    {
        int n = x % m;
        if (n >= 10)
        {
            ans += n - 10 + 'A';
        }
        else
        {
            ans += '0' + n;
        }
        x /= m;
    } while (x);
    while (ans.data()[i] != '\0')
    {
        i++;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        cout << ans.data()[j];
    }
    cout << endl;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
bool IsPrime[N];
int n;
int main()
{
    cin >> n;
    fill(IsPrime, IsPrime + n + 1, true);
    IsPrime[0] = IsPrime[1] = false;
    for (int i = 2; i <= n; i++)
        if (IsPrime[i])
        {
            cout << i << " ";
            for (int j = 1; i * j <= n; j++)
                IsPrime[i * j] = false;
        }
    cout << endl;
    return 0;
}
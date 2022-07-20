#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, Status[N];
int main()
{
    cin >> n;
    cout << n << endl;
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j < i + 1; j++)
                cout << 0;
            for (int j = 0; j < n - i - 1; j++)
                cout << 1;
        }
        else
        {
            for (int j = 0; j < i + 1; j++)
                cout << 1;
            for (int j = 0; j < n - i - 1; j++)
                cout << 0;
        }
        cout << endl;
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
    cin >> n;
    while (n != 1)
    {
        if (n % 2)
        {
            cout << n << "*3+1=";
            n = n * 3 + 1;
        }
        else
        {
            cout << n << "/2=";
            n /= 2;
        }
        cout << n << endl;
    }
    cout << "End" << endl;
    return 0;
}
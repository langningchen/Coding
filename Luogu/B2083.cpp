#include <bits/stdc++.h>
using namespace std;
int a, b, f;
char c;
int main()
{
    cin >> a >> b >> c >> f;
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
            if (f != 0 || i == 0 || i == a - 1 || j == 0 || j == b - 1)
                cout << c;
            else
                cout << " ";
        cout << endl;
    }
    return 0;
}
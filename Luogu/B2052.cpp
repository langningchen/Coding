#include <bits/stdc++.h>
using namespace std;
int a, b;
char c;
int main()
{
    cin >> a >> b >> c;
    if (c == '+')
        cout << a + b << endl;
    else if (c == '-')
        cout << a - b << endl;
    else if (c == '*')
        cout << a * b << endl;
    else if (c == '/')
    {
        if (b == 0)
            cout << "Divided by zero!" << endl;
        else
            cout << a / b << endl;
    }
    else
        cout << "Invalid operator!" << endl;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
double a, b, c, x1, x2;
int main()
{
    cin >> a >> b >> c;
    if (b * b - 4 * a * c < 0)
    {
        cout << "No answer!" << endl;
        return 0;
    }
    x1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    x2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    if (x1 == x2)
        cout << fixed << setprecision(5) << "x1=x2=" << x1 << endl;
    else
        cout << fixed << setprecision(5) << "x1=" << x1 << ";x2=" << x2 << endl;
    return 0;
}
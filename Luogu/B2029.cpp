#include <bits/stdc++.h>
using namespace std;
const double PI = 3.1415926;
int h, r;
int main()
{
    cin >> h >> r;
    cout << ceil(20000.0 / (PI * r * r * h)) << endl;
    return 0;
}
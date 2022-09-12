#include <bits/stdc++.h>
using namespace std;
int x, y;
int main()
{
    cin >> x >> y;
    cout << (x < y ? "<" : (x == y ? "=" : ">")) << endl;
    return 0;
}
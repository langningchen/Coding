#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
struct Blanket
{
    int a, b, g, k, id;
};
int x, y, n;
vector<Blanket> Blankets;
bool InBlanket(Blanket CheckBlanket)
{
    if (x >= CheckBlanket.a &&
        x <= CheckBlanket.a + CheckBlanket.g &&
        y >= CheckBlanket.b &&
        y <= CheckBlanket.b + CheckBlanket.k)
        return true;
    return false;
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Blanket Temp;
        Temp.id = i;
        cin >> Temp.a >> Temp.b >> Temp.g >> Temp.k;
        Blankets.push_back(Temp);
    }
    cin >> x >> y;
    int Ans = -1;
    for (int i = 0; i < Blankets.size(); i++)
        if (InBlanket(Blankets[i]))
            Ans = i + 1;
    cout << Ans << endl;
    return 0;
}

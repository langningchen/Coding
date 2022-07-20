#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll Money, Save;
int main()
{
    for (int i = 0; i < 12; i++)
    {
        ll Use;
        cin >> Use;
        Money += 300;
        if (Use > Money)
        {
            cout << -i - 1 << endl;
            return 0;
        }
        Money -= Use;
        Save += Money / 100;
        Money %= 100;
    }
    cout << Save * 120 + Money << endl;
    return 0;
}

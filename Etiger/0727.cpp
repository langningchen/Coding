#include <bits/stdc++.h>
using namespace std;
stack<int> s;
int n, t;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        while (s.size() == 0 || s.top() != a)
        {
            s.push(t + 1);
            t++;
            if (t > n)
            {
                cout << "No" << endl;
                return 0;
            }
        }
        s.pop();
    }
    cout << "Yes" << endl;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
const int INF = 0x7FFFFFFF;
ll a, b;
string ans;
int main()
{
    ios::sync_with_stdio(false);
    while (1)
    {
        system("/workspaces/Coding/Etiger/186/unit05/SH-18605chenlangning/digit/Generater");
        system("/workspaces/Coding/Etiger/186/unit05/SH-18605chenlangning/digit/digit");
        ifstream InputFileStream("/workspaces/Coding/Etiger/186/unit05/SH-18605chenlangning/digit/digit.in");
        ifstream OutputFileStream("/workspaces/Coding/Etiger/186/unit05/SH-18605chenlangning/digit/digit.out");
        InputFileStream >> a >> b;
        OutputFileStream >> ans;
        ll t = a + b;
        if (t < 0)
        {
            if (ans[0] != '-')
            {
                cout << "ERROR" << endl;
                return 0;
            }
            t = -t;
        }
        for (int i = (log10(t) + 1) % 3; i < ans.size(); i += 3)
            ans.erase(i, 1);
        for (int i = 0; i < ans.size(); i++)
        {
            ll ans;
            OutputFileStream >> ans;
            if (Movies[i].e >= Movies[ans - 1].s)
            {
                cout << "ERROR" << endl;
                return 0;
            }
        }
        cout << "OK" << endl;
        InputFileStream.close();
        OutputFileStream.close();
    }
    return 0;
}
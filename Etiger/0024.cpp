#include <bits/stdc++.h>
using namespace std;
string String;
map<char, int> Map;
stack<int> Stack;
bool Success = true;
int main()
{
    cin >> String;
    Map['<'] = 1;
    Map['>'] = 2;
    Map['('] = 3;
    Map[')'] = 4;
    Map['['] = 5;
    Map[']'] = 6;
    Map['{'] = 7;
    Map['}'] = 8;
    for (int i = 0; i < String.size(); ++i)
        if (Stack.empty())
            Stack.push(Map[String[i]]);
        else if (Map[String[i]] % 2 != 0)
        {
            if (Map[String[i]] <= Stack.top())
                Stack.push(Map[String[i]]);
            else
            {
                cout << "NO" << endl;
                return 0;
            }
        }
        else if (Map[String[i]] - 1 == Stack.top())
            Stack.pop();
    if (!Stack.empty())
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
    return 0;
}

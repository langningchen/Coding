#include <bits/stdc++.h>
using namespace std;
string s;
map<string, int> two;
map<string, int> three;
int main()
{
    getline(cin, s);
    for (int i = 0; i < s.size() - 2; i++)
    {
        if (((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) && ((s[i + 1] >= 'a' && s[i + 1] <= 'z') || (s[i + 1] >= 'A' && s[i + 1] <= 'Z')))
        {
            string temp = "";
            temp += s[i];
            temp += s[i + 1];
            two[temp]++;
            if (((s[i + 2] >= 'a' && s[i + 2] <= 'z') || (s[i + 2] >= 'A' && s[i + 2] <= 'Z')))
            {
                temp += s[i + 2];
                three[temp]++;
            }
        }
    }
    \r if (((s[s.size() - 1] >= 'a' && s[s.size() - 1] <= 'z') || (s[s.size() - 1] >= 'A' && s[s.size() - 1] <= 'Z')) && ((s[s.size()] >= 'a' && s[s.size()] <= 'z') || (s[s.size()] >= 'A' && s[s.size()] <= 'Z')))
    {
        string temp = "";
        temp += s[s.size() - 1];
        temp += s[s.size()];
        two[s]++;
    }
    int two_max = 0, three_max = 0;
    for (map<string, int>::iterator mit = two.begin(); mit != two.end(); mit++)
    {
        if (mit->second > two_max)
            two_max = mit->second;
    }
    for (map<string, int>::iterator mit = two.begin(); mit != two.end(); mit++)
    {
        if (mit->second == two_max)
        {
            cout << mit->first << endl;
            break;
        }
    }
    for (map<string, int>::iterator mit = three.begin(); mit != three.end(); mit++)
    {
        if (mit->second > three_max)
            three_max = mit->second;
    }
    for (map<string, int>::iterator mit = three.begin(); mit != three.end(); mit++)
    {
        if (mit->second == three_max)
        {
            cout << mit->first << endl;
            break;
        }
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll ToDec(string Input)
{
    ll Output = 0;
    for (size_t i = 0; i < Input.size(); i++)
        Output = Output * 26 + Input[i] - 'A' + 1;
    return Output;
}
string FromHex(int Input)
{
    Input--;
    string Output = "";
    do
    {
        Output.push_back(Input % 26 + 'A');
        Input = Input / 26 - 1;
    } while (Input >= 0);
    reverse(Output.begin(), Output.end());
    return Output;
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        vector<string> v;
        int last = 0;
        for (size_t i = 1; i < s.size() + 1; i++)
            if (i == s.size() ||
                (s[i - 1] >= 'A' && s[i - 1] <= 'Z' && s[i] >= '0' && s[i] <= '9') ||
                (s[i - 1] >= '0' && s[i - 1] <= '9' && s[i] >= 'A' && s[i] <= 'Z'))
            {
                v.push_back(s.substr(last, i - last));
                last = i;
            }
        if (v.size() == 2)
            cout << "R" << v[1] << "C" << ToDec(v[0]) << endl;
        else
            cout << FromHex(atoi(v[3].c_str())) << v[1] << endl;
    }
    return 0;
}
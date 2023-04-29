#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int INF = 0x7FFF'FFFF;
string s;
int dp[N][N];
string Repeat(string Data, int Times)
{
    string Output = "";
    for (int i = 0; i < Times; i++)
        Output += Data;
    return Output;
}
int F(int i, int j)
{
    if (i + 3 >= j)
        dp[i][j] = j - i + 1;
    else if (dp[i][j] == INF)
        for (int k = i; k <= j; k++)
        {
            int x = (j - i + 1) / (k - i + 1);
            if (s.substr(i, j - i + 1) == Repeat(s.substr(i, k - i + 1), x))
                dp[i][j] = min(dp[i][j], F(i, k) + 2 + (int)ceil(log10(x + 1)));
            else
                dp[i][j] = min(dp[i][j], F(i, k) + F(k + 1, j));
        }
    return dp[i][j];
}
int main()
{
    cin >> s;
    for (int i = 0; i < s.size(); i++)
        for (int j = 0; j < s.size(); j++)
            dp[i][j] = INF;
    cout << F(0, s.size() - 1) << endl;
    return 0;
}

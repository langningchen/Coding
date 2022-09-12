#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 15;
const int INF = 0x7FFFFFFF;
struct Info
{
    int Value;
    vector<pair<int, int>> History;
};
ll n, Ans, Map[N][N];
Info Dp[N][N];
void DP()
{
    memset(Dp, 0, sizeof(Dp));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == 0 && j == 0)
            {
                Dp[i][j].Value = Map[i][j];
                if (Map[i][j] != 0)
                    Dp[i][j].History.push_back(make_pair(i, j));
            }
            else if (i == 0)
            {
                Dp[i][j].Value = Map[i][j] + Map[i][j - 1];
                if (Map[i][j - 1] != 0)
                    Dp[i][j].History.push_back(make_pair(i, j - 1));
            }
            else if (j == 0)
            {
                Dp[i][j].Value = Map[i][j] + Map[i - 1][j];
                if (Map[i - 1][j] != 0)
                    Dp[i][j].History.push_back(make_pair(i - 1, j));
            }
            else
            {
                if (Dp[i - 1][j].Value > Dp[i][j - 1].Value)
                {
                    Dp[i][j].Value = Dp[i - 1][j].Value + Map[i][j];
                    Dp[i][j].History = Dp[i - 1][j].History;
                    if (Map[i - 1][j] != 0)
                        Dp[i][j].History.push_back(make_pair(i - 1, j));
                }
                else
                {
                    Dp[i][j].Value = Dp[i][j - 1].Value + Map[i][j];
                    Dp[i][j].History = Dp[i][j - 1].History;
                    if (Map[i][j - 1] != 0)
                        Dp[i][j].History.push_back(make_pair(i, j - 1));
                }
            }
        }
    Ans += Dp[n - 1][n - 1].Value;
}
int main()
{
    cin >> n;
    int x, y, d;
    while (x != 0 || y != 0 || d != 0)
    {
        cin >> x >> y >> d;
        Map[x - 1][y - 1] = d;
    }
    DP();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << Map[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << Dp[i][j].Value << "\t";
        cout << endl;
    }
    cout << endl;
    for (vector<pair<int, int>>::iterator vit = Dp[n - 1][n - 1].History.begin(); vit != Dp[n - 1][n - 1].History.end(); vit++)
    {
        Map[vit->first][vit->second] = 0;
    }
    DP();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << Map[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << Dp[i][j].Value << "\t";
        cout << endl;
    }
    cout << endl;
    cout << Ans << endl;
    return 0;
}

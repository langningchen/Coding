#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
const int INF = 0x7FFFFFFF;
ll n;
struct movie
{
    ll s, e, id;
} Movies[N];
int main()
{
    ios::sync_with_stdio(false);
    while (1)
    {
        system("/workspaces/Coding/Etiger/186/unit05/SH-18605chenlangning/movie/Generater");
        system("/workspaces/Coding/Etiger/186/unit05/SH-18605chenlangning/movie/movie");
        ifstream InputFileStream("/workspaces/Coding/Etiger/186/unit05/SH-18605chenlangning/movie/movie.in");
        ifstream OutputFileStream("/workspaces/Coding/Etiger/186/unit05/SH-18605chenlangning/movie/movie.out");
        InputFileStream >> n;
        for (int i = 0; i < n; i++)
            InputFileStream >> Movies[i].s;
        for (int i = 0; i < n; i++)
            InputFileStream >> Movies[i].e;
        Movies[n].s = INF;
        for (int i = 0; i < n; i++)
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
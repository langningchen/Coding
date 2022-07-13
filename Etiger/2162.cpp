#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
struct SubTree
{
    int Left;
    int Right;
};
int n, m, DFN[N], Timer;
vector<int> AdjacencyTable[N];
vector<int> Output;
SubTree Tree[N];
void DFS(int Now, int Father)
{
    Output.push_back(Now);
    Timer++;
    Tree[Now].Left = DFN[Now] = Timer;
    for (int i = 0; i < AdjacencyTable[Now].size(); i++)
    {
        if (AdjacencyTable[Now][i] != Father)
        {
            DFS(AdjacencyTable[Now][i], Now);
            Output.push_back(Now);
        }
    }
    Timer++;
    Tree[Now].Right = Timer;
}
int main()
{
    freopen("euler.in", "r", stdin);
    freopen("euler.out", "w", stdout);
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        AdjacencyTable[a].push_back(b);
        AdjacencyTable[b].push_back(a);
    }
    DFS(1, 1);
    for (int i = 0; i < 2 * n - 2; i++)
    {
        cout << Output[i] << " ";
    }
    cout << Output[2 * n - 2] << endl;
    for (int i = 1; i < n; i++)
    {
        cout << Tree[i].Left << " ";
    }
    cout << Tree[n].Left << endl;
    for (int i = 1; i < n; i++)
    {
        cout << Tree[i].Right - 1 << " ";
    }
    cout << Tree[n].Right - 1 << endl;
    return 0;
}

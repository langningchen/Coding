#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
char Temp[N];
string s;
void DFS(int i)
{
    if (i == 0)
    {
        printf("YES\n");
        exit(0);
    }
    if (i >= 4 && s.substr(i - 4, 4) == "work")
        DFS(i - 4);
    if (i >= 6 && s.substr(i - 6, 6) == "worker")
        DFS(i - 6);
    if (i >= 5 && s.substr(i - 5, 5) == "erase")
        DFS(i - 5);
    if (i >= 6 && s.substr(i - 6, 6) == "eraser")
        DFS(i - 6);
}
int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%s", Temp);
    s = Temp;
    DFS(s.size());
    printf("NO\n");
    return 0;
}
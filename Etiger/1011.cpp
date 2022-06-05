#include <bits/stdc++.h>
using namespace std;

const int MAX = 40005;

struct SubTree{
    int Left;
    int Right;
};

int n, m, DFN[MAX], Timer;
vector<int> AdjacencyTable[MAX];
SubTree Tree[MAX];
void DFS(int Now, int Father) {
    Timer++;
    Tree[Now].Left = DFN[Now] = Timer;
    for (int i = 0; i < AdjacencyTable[Now].size(); i++) {
        if (AdjacencyTable[Now][i] != Father) {
            DFS(AdjacencyTable[Now][i], Now);
        }
    }
    Tree[Now].Right = Timer;
}
bool Ancestor(int Now, int Father) {
    return Tree[Now].Left < Tree[Father].Left && Tree[Father].Right <= Tree[Now].Right;
}
int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    cin >> n;
    int root;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (b == -1) {
            root = a;
        }
        else {
            AdjacencyTable[a].push_back(b);
            AdjacencyTable[b].push_back(a);
        }
    }
    DFS(root, root);
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (Ancestor(x, y)) {
            cout << 1 << endl;
        }
        else if (Ancestor(y, x)) {
            cout << 2 << endl;
        }
        else {
            cout << 0 << endl;
        }
    }
    return 0;
}

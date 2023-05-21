#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 505;
const ll INF = 0x3FFF'FFFF'FFFF'FFFF;
enum DIRECTION
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
struct EDGE
{
    ll NextEdge;
    ll v;
    ll w;
} Edges[N * N * 8];
ll n, m, Start, End, Head[N * N], EdgeCount, NearestWall[N][N], FirstWall[N][N][4], Distance[N * N];
bool IsWall[N][N];
queue<pair<ll, ll>> WallQueue;
void AddEdge(ll u, ll v, ll w)
{
    Edges[++EdgeCount].NextEdge = Head[u];
    Edges[EdgeCount].v = v;
    Edges[EdgeCount].w = w;
    Head[u] = EdgeCount;
}
ll Coordinate(ll x, ll y)
{
    return (x - 1) * m + y;
}
void Input()
{
    scanf("%lld %lld", &n, &m);
    getchar();
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= m; j++)
        {
            char Temp;
            scanf("%c", &Temp);
            if (Temp == 'C')
                Start = Coordinate(i, j);
            else if (Temp == 'F')
                End = Coordinate(i, j);
            else if (Temp == '#')
                WallQueue.push({i, j});
            if (Temp != '#')
                IsWall[i][j] = true;
        }
        getchar();
    }
}
void GetWall()
{
    while (!WallQueue.empty())
    {
        auto [x, y] = WallQueue.front();
        WallQueue.pop();
        const ll dx[] = {-1, 0, 0, 1};
        const ll dy[] = {0, -1, 1, 0};
        for (ll i = 0; i < 4; i++)
        {
            ll nx = x + dx[i];
            ll ny = y + dy[i];
            if (IsWall[nx][ny] && !NearestWall[nx][ny])
            {
                NearestWall[nx][ny] = NearestWall[x][y] + 1;
                WallQueue.push({nx, ny});
            }
        }
    }
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++)
            if (IsWall[i][j])
            {
                FirstWall[i][j][LEFT] = (IsWall[i][j - 1] ? FirstWall[i][j - 1][LEFT] : Coordinate(i, j));
                FirstWall[i][j][UP] = (IsWall[i - 1][j] ? FirstWall[i - 1][j][UP] : Coordinate(i, j));
            }
    for (ll i = n; i; i--)
        for (ll j = m; j; j--)
            if (IsWall[i][j])
            {
                FirstWall[i][j][RIGHT] = (IsWall[i][j + 1] ? FirstWall[i][j + 1][RIGHT] : Coordinate(i, j));
                FirstWall[i][j][DOWN] = (IsWall[i + 1][j] ? FirstWall[i + 1][j][DOWN] : Coordinate(i, j));
            }
}
void BuildMap()
{
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++)
            if (IsWall[i][j])
            {
                if (IsWall[i][j + 1])
                {
                    AddEdge(Coordinate(i, j), Coordinate(i, j + 1), 1);
                    AddEdge(Coordinate(i, j + 1), Coordinate(i, j), 1);
                }
                if (IsWall[i + 1][j])
                {
                    AddEdge(Coordinate(i, j), Coordinate(i + 1, j), 1);
                    AddEdge(Coordinate(i + 1, j), Coordinate(i, j), 1);
                }
                auto Do = [i, j](DIRECTION Direction)
                {
                    if (FirstWall[i][j][Direction] != Coordinate(i, j))
                        AddEdge(Coordinate(i, j), FirstWall[i][j][Direction], NearestWall[i][j]);
                };
                Do(UP);
                Do(DOWN);
                Do(LEFT);
                Do(RIGHT);
            }
}
void Dijkstra()
{
    bool Visited[N * N] = {false};
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> DijkstraQueue;
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++)
            Distance[Coordinate(i, j)] = INF;
    DijkstraQueue.push({0, Start});
    Distance[Start] = 0;
    while (!DijkstraQueue.empty())
    {
        ll u = DijkstraQueue.top().second;
        DijkstraQueue.pop();
        if (Visited[u])
            continue;
        Visited[u] = true;
        for (ll i = Head[u]; i; i = Edges[i].NextEdge)
        {
            ll v = Edges[i].v;
            if (Distance[v] > Distance[u] + Edges[i].w)
            {
                Distance[v] = Distance[u] + Edges[i].w;
                DijkstraQueue.push({Distance[v], v});
            }
        }
    }
}
int main()
{
    freopen("cell.in", "r", stdin);
    freopen("cell.out", "w", stdout);
    Input();
    GetWall();
    BuildMap();
    Dijkstra();
    if (Distance[End] == INF)
        printf("no\n");
    else
        printf("%lld\n", Distance[End]);
    return 0;
}

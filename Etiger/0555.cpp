#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 40009;
const ll M = 100009;
struct edge{ll a, b, c;} e[M];
ll n, m, id[N];
ll find(ll x) {return id[x] == x ? x : id[x] = find(id[x]);}
void unite(ll x, ll y) {ll fx = find(x), fy = find(y); id[fx] = fy;}
bool cmp(const edge &x, const edge &y) {return x.c > y.c;} 
int main() {
	freopen("prison.in", "r", stdin);
	freopen("prison.out", "w", stdout); 
	cin >> n >> m;
	for (int i = 0; i < m; i++) cin >> e[i].a >> e[i].b >> e[i].c;
	sort(e, e + m, cmp);
	for (int i = 1; i <= n + n; i++) id[i] = i;
	ll ans = 0;
	for (int i = 0; i < m; i++) {
		ll fa = find(e[i].a), fb = find(e[i].b);
		if (fa == fb) {
			ans = e[i].c;
			break; 
		} 
		unite(e[i].a, e[i].b + n);
		unite(e[i].b, e[i].a + n);
	}
	cout << ans << endl;
	return 0;
}
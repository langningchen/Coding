#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
char type[4];
int typelen, n;
ll q, addr;
int main()
{
	freopen("address.in", "r", stdin);
	freopen("address.out", "w", stdout);
	cin >> type >> n >> addr >> q;
	if (strcmp(type, "int") == 0)
		typelen = 4;
	else
		typelen = 1;
	if (addr + n * typelen >= q && q >= addr)
		cout << (q - addr) / typelen << endl;
	else
		cout << "Error" << endl;
	return 0;
}

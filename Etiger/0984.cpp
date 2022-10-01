#include <bits/stdc++.h>
using namespace std;
string name, id;
int main()
{
	freopen("identification.in", "r", stdin);
	freopen("identification.out", "w", stdout);
	getline(cin, name);
	getline(cin, id);
	cout << name << " was born in ";
	cout << id.substr(6, 4) << "." << endl;
	return 0;
}

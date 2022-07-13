#include <bits/stdc++.h>
using namespace std;
struct node
{
	int n;
	string str;
	bool operator>(const node *cmp) const
	{
		return this->str > cmp->str;
	}
};
\r
	vector<node>
		v;
bool OK(string s, int a)
{
	if (s == "0")
	{
		return true;
	}
	if (s[0] == '0' || s == "")
	{
		return false;
	}
	if (a == 255)
	{
		if (s.size() > 3)
		{
			return false;
		}
	}
	else
	{
		if (s.size() > 5)
		{
			return false;
		}
	}
	int temp = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] > '9' || s[i] < '0')
		{
			return false;
		}
		temp += (s[i] - '0') * pow(10, (s.size() - i - 1));
	}
	if (temp > a)
	{
		return false;
	}
	return true;
}
int main()
{
	freopen("network.in", "r", stdin);
	freopen("network.out", "w", stdout);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int flag = 0;
		string s1, s2, temp, check;
		cin >> s1 >> s2;
		check = s2;
		for (int j = 0; j < 4; j++)
		{
			char c = '.';
			if (j == 3)
			{
				c = ':';
			}
			if (check.find(c) == check.npos)
			{
				flag = 1;
				break;
			}
			temp = check.substr(0, check.find(c));
			check.erase(0, check.find(c) + 1);
			if (!OK(temp, 255))
			{
				flag = 2;
				break;
			}
		}
		if (flag == 0)
		{
			if (!OK(check, 65535))
			{
				flag = 3;
			}
		}
		if (flag != 0)
		{
			cout << "ERR" << endl;
			continue;
		}
		else
		{
			node temp;
			temp.n = i;
			temp.str = s2;
			if (s1 == "Server")
			{
				bool flag = false;
				for (vector<node>::iterator vit = v.begin(); vit != v.end(); vit++)
				{
					if (vit->str == s2)
					{
						flag = true;
						break;
					}
				}
				if (flag == true)
				{
					cout << "FAIL" << endl;
					continue;
				}
				v.insert(v.end(), temp);
				cout << "OK" << endl;
			}
			else
			{
				bool flag = false;
				for (vector<node>::iterator vit = v.begin(); vit != v.end(); vit++)
				{
					if (vit->str == s2)
					{
						flag = true;
						cout << vit->n << endl;
						break;
					}
				}
				if (flag == false)
				{
					cout << "FAIL" << endl;
				}
			}
		}
	}
	return 0;
}

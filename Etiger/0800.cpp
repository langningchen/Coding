#include <bits/stdc++.h>
using namespace std;
string s1, s2, ans;
int pos_start = -1, pos_end = -1, times, Find;
string i2s(int i)
{
	string temp, ans;
	ans = "";
	while (i > 0)
	{
		temp += i % 10 + '0';
		i /= 10;
	}
	for (int j = temp.size() - 1; j >= 0; j--)
	{
		ans += temp.data()[j];
	}
	ans += '\0';
	return ans;
}
int main()
{
	freopen("zfcbh.in", "r", stdin);
	freopen("zfcbh.out", "w", stdout);
	getline(cin, s1);
	while (1)
	{
		Find = 0;
		times = 0;
		pos_start = -1;
		pos_end = -1;
		for (unsigned int i = 0; i < s1.size(); i++)
		{
			if (i == s1.size() - 1 && pos_end != -1 && pos_start != -1)
			{
				s2 = s1.substr(pos_end + 2, s1.size() - 1);
				s2 += s1[i] - 32;
				s2 += i2s(times + 1).data();
				s2 += s1.substr(0, pos_start);
				Find = 1;
				break;
			}
			else
			{
				if (s1[i] == s1[i + 1] && s1[i] >= 'a' && s1[i] <= 'z')
				{
					pos_end = i;
					times++;
					if (pos_start == -1)
						pos_start = pos_end;
				}
				else if (pos_end != -1 && pos_start != -1)
				{
					s2 = s1.substr(pos_end + 2, s1.size() - 1);
					s2 += s1[i] - 32;
					s2 += i2s(times + 1).data();
					s2 += s1.substr(0, pos_start);
					Find = 1;
					break;
				}
				else
				{
					pos_end = -1;
					pos_start = -1;
				}
			}
		}
		if (Find == 0)
		{
			cout << s1 << endl;
			break;
		}
		Find = 0;
		times = 0;
		pos_start = -1;
		pos_end = -1;
		for (unsigned int i = 0; i < s2.size() - 1; i++)
		{
			if (i == s1.size() - 1 && pos_end != -1 && pos_start != -1)
			{
				s2 = s1.substr(pos_end + 2, s1.size() - 1);
				s2 += s1[i] - 32;
				s2 += i2s(times + 1).data();
				s2 += s1.substr(0, pos_start);
				Find = 1;
				break;
			}
			else
			{
				if (s2[i] == s2[i + 1] && s2[i] >= 'a' && s2[i] <= 'z')
				{
					pos_end = i;
					times++;
					if (pos_start == -1)
						pos_start = pos_end;
				}
				else if (pos_end != -1 && pos_start != -1)
				{
					s1 = s2.substr(pos_end + 2, s2.size() - 1);
					s1 += s2[i] - 32;
					s1 += i2s(times + 1).data();
					s1 += s2.substr(0, pos_start);
					Find = 1;
					break;
				}
				else
				{
					pos_end = -1;
					pos_start = -1;
				}
			}
		}
		if (Find == 0)
		{
			cout << s2 << endl;
			break;
		}
	}
	return 0;
}

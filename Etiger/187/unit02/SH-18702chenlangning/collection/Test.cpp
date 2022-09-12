#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(false);
	for (ll i = 45000; ; i++)
	{
		cout << i << endl;
		ofstream InputFileOutputStream("collection.in");
		InputFileOutputStream << i << endl;
		InputFileOutputStream.close();
		clock_t Start = clock();
		system("./collection");
		clock_t End = clock();
		if (End - Start > CLOCKS_PER_SEC)
		{
			cout << "collection TLE" << endl;
			break;
		}	
		clock_t Start_BF = clock();
		system("./collection-BF");
		clock_t End_BF = clock();
		if (End_BF - Start_BF > CLOCKS_PER_SEC)
		{
			cout << "collection-BF TLE" << endl;
			break;
		}
		ifstream OutputFileInputStream("collection.out");
		ll Answer;
		OutputFileInputStream >> Answer;
		OutputFileInputStream.close();
		ifstream OutputFileInputStream_BF("collection-BF.out");
		ll Answer_BF;
		OutputFileInputStream_BF >> Answer_BF;
		OutputFileInputStream_BF.close();
		if (Answer != Answer_BF)
			break;
	}
	cout << "Error" << endl;
	return 0;
}

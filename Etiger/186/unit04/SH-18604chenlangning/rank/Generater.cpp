#include <bits/stdc++.h>
using namespace std;
vector<string> NameList;
int main()
{
    freopen("rank.in", "w", stdout);
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        string Name;
        int t = rand() % 4 + 7;
        for (int j = 0; j < t; j++)
        {
            Name.push_back(rand() % 2 ? rand() % 26 + 'a' : rand() % 26 + 'A');
        }
        NameList.push_back(Name);
    }
    cout << 10000 << endl;
    for (int i = 0; i < 10000; i++)
    {
        int n = 0;
        vector<int> teststudent;
        for (int j = 0; j < 100; j++)
            if (rand() % 2)
            {
                n++;
                teststudent.push_back(j);
            }
        cout << n << endl;
        for (vector<int>::iterator vit = teststudent.begin(); vit != teststudent.end(); vit++)
            cout << NameList[*vit] << " " << rand() % 1000 << endl;
    }
    cout << endl;
    return 0;
}

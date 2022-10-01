#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 105;
const int N = 10005;
const int INF = 0x7FFFFFFF;
struct Student
{
    string name;
    int tot;
} s[M];
int nTests, scores[M][N];
map<string, int> id;
bool cmp(Student &cmp1, Student &cmp2)
{
    if (cmp1.tot != cmp2.tot)
        return cmp1.tot > cmp2.tot;
    else
        return cmp1.name < cmp2.name;
}
int count(int Data)
{
    if (Data == 0)
        return 1;
    else
        return log10(Data) + 1;
}
void printName(string Name, int Length)
{
    cout << Name;
    for (unsigned int i = 0; i < Length - Name.size(); i++)
        cout << "_";
}
void printScore(int Score, int Length)
{
    if (Score == -1)
    {
        for (int i = 0; i < Length; i++)
            cout << "_";
    }
    else
    {
        cout << Score;
        for (int i = 0; i < Length - count(Score); i++)
            cout << "_";
    }
}
int main()
{
    freopen("rank.in", "r", stdin);
    freopen("rank.out", "w", stdout);
    cin >> nTests;
    memset(scores, -1, sizeof(scores));
    int nStu = 0;
    for (int k = 1; k <= nTests; k++)
    {
        int x;
        cin >> x;
        for (int i = 1; i <= x; i++)
        {
            string name;
            int score;
            cin >> name >> score;
            if (id.count(name))
                s[id[name]].tot += score;
            else
            {
                id[name] = ++nStu;
                s[id[name]].name = name;
                s[id[name]].tot = score;
            }
            scores[id[name]][k] = score;
        }
    }
    int mxLen = 0;
    for (int i = 1; i <= nStu; i++)
        mxLen = max(mxLen, (int)s[i].name.size());
    sort(s + 1, s + 1 + nStu, cmp);
    int nDigits = count(s[1].tot);
    for (int i = 1; i <= nStu; i++)
    {
        printName(s[i].name, mxLen);
        cout << " ";
        printScore(s[i].tot, nDigits);
        cout << ":";
        for (int k = 1; k <= nTests; k++)
        {
            cout << " ";
            printScore(scores[id[s[i].name]][k], 3);
        }
        cout << endl;
    }
    return 0;
}
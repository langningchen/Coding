#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 15;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll d, g, p[N], c[N], Answer = INF;
int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%lld%lld", &d, &g);
    g /= 100;
    for (ll i = 1; i <= d; i++)
    {
        scanf("%lld%lld", &p[i], &c[i]);
        c[i] /= 100;
    }
    for (ll i = 0; i < (1 << d); i++)
    {
        ll Score = 0, QuestionToDo = 0, MaxN = 0;
        for (ll j = 1; j <= d; j++)
            if (i & (1 << (j - 1)))
            {
                Score += p[j] * j + c[j];
                QuestionToDo += p[j];
            }
            else
                MaxN = j;
        if (Score >= g)
            Answer = min(Answer, QuestionToDo);
        else if (MaxN != 0)
        {
            ll Temp = (g - Score + MaxN - 1) / MaxN;
            if (Temp < p[MaxN])
            {
                QuestionToDo += Temp;
                Answer = min(Answer, QuestionToDo);
            }
        }
    }
    printf("%lld\n", Answer);
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
char n[256],ans[256];
int main() {
    int i = 0;
    cin>>n;
    if (strcmp(n,"0") == 0)
    {
        cout<<"0";
        return 0;
    }
    for (int i = 0; i<strlen(n); i++)
    {
        ans[strlen(n)-i-1] = n[i];
    }
    ans[strlen(n)] = '\0';
    if (ans[strlen(ans)-1] == '-')
        cout<<'-';
    while (ans[i] == '0')
    {
            i++;
    }
    for (; i<strlen(ans); i++)
    {
        if (ans[i] != '-')
            cout<<ans[i];
    }
    return 0;
}


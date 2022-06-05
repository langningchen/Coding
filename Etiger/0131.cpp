#include<bits/stdc++.h>
using namespace std;
int main() {
    freopen("caesar.in","r",stdin);
    freopen("caesar.out","w",stdout);
    string s;
    getline(cin,s);
    for (int i=0; i<s.size(); i++)
    {
        if(s[i]==' ') cout<<' ';
        else if(s[i]=='z') cout<<'a';
        else cout<<char(s[i]+1);
    }
    return 0;
}


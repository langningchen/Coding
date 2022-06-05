#include<bits/stdc++.h>
using namespace std;
int main() {
    freopen("ceasar.in","r",stdin);
    freopen("ceasar.out","w",stdout);
    char c[3],o[3];
    cin>>c[0]>>c[1]>>c[2];
    for (int i=0; i<3; i++) //逐个处理
    {
        o[i] = (c[i]-'a'+1)%26+'a'; //计算
    }
    cout<<o[0]<<" "<<o[1]<<" "<<o[2]<<endl;
    return 0;
}


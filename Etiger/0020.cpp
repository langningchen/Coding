#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    int j;
    cin>>n;
    for(int i=1;i<=n;i++){
        for(j=0;j<n-i;j++)
            cout<<" ";
        for(j=1;j<i*2;j++)
            cout<<"*";
        cout<<endl;
    }
    for(int i=n-1;i>0;i--){
        for(j=0;j<n-i;j++)
            cout<<" ";
        for(j=1;j<i*2;j++)
            cout<<"*";
        cout<<endl;
    }
    return 0;
}


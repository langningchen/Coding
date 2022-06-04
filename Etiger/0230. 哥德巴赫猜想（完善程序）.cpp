#include<iostream>
using namespace std;
int main(){
    const int SIZE=1000;
    int n,r,p[SIZE],i,j,k,ans;
    bool tmp;
    cin>>n;
    r=1;
    p[1]=2;
    for(i=3;i<=n;i++){
        tmp=true;
        for(j=1;j<=r;j++)
            if(i%p[j]==0){
                tmp=false;
                break;
            }
        if(tmp){
            r++;
            p[r]=i;
        }
    }
    ans=0;
    for(i=2;i<=n/2;i++){
        tmp=false;
        for(j=1;j<=r;j++)
            for(k=j;k<=r;k++)
                if(i+i==p[j]+p[k]){
                    tmp=true;
                    break;
                }
        if(tmp)
            ans++;
    }
    cout<<ans<<endl;
    return 0;
}

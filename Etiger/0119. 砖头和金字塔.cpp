#include<iostream>
using namespace std;
int n; char c;
void pyramid(int m,char x){
    for (int i = 1; i <= m; i ++)
    {
        for (int n = (m - i); n > 0; n--)
            cout<<' ';
        for (int n = 0; n < (2 * i - 1); n++)
            cout<<x;
        cout<<endl;
    }
}
int main(){
    cin>>n>>c;
    pyramid(n,c);
    pyramid(2*n,c);
    return 0;
}


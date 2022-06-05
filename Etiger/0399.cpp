#include <iostream>
#include <algorithm>
#define N 10005
using namespace std;
struct point{int pos,tag;};
bool cmp(const point&a,const point&b){
    return a.pos<b.pos||a.pos==b.pos&&a.tag<b.tag; 
}
int to_int(string s) {
    return (s[0] - '0') * 10 + (s[1] - '0');
}
point d[N];
int main() {
    int n,cnt=0,ans=0;
    cin>>n;
    for(int i=0;i<n+n;i+=2) {
        string s;
        cin >> s;
        d[i].pos = to_int(s.substr(0, 2)) * 60 + to_int(s.substr(3, 2));
        d[i+1].pos = to_int(s.substr(6, 2)) * 60 + to_int(s.substr(9, 2));
//        cout << d[i].pos << d[i+1].pos << endl;
        int temp;
        cin >> temp; 
        d[i].tag=temp;
        d[i+1].tag=-temp;
    }
    sort(d,d+n+n,cmp);
    for(int i=0;i<n+n;i++){
        cnt+=d[i].tag;
        ans=max(ans,cnt);
    }
    cout<<ans<<endl;
    return 0;
}

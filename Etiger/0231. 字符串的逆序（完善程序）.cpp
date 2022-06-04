#include <iostream>
#include <cstring>
using namespace std;
int maxline=200,kz;
int reverse(char s[])
{
    int i,j,t;
    for(i=0,j=strlen(s)-1; i<j;i++,j--)
    {
        t=s[i]; s[i]=s[j]; s[j]=t;
    }   
    return 0;  
} 
int main(){ 
    char line[100];   
    cin>>kz;   
    while(kz!=-1)     
    { 
        cin>>line;  
        reverse(line); 
        cout<<line<<endl;       
        cin>>kz;      
    }
    return 0;
}

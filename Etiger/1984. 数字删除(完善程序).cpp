#include <iostream>
using namespace std;
const int SIZE = 30;
int delnum(char *s) {
    int i, j;
    j = 0;
    for (i =0; s[i] !='\0'; i++)
        if (s[i] < '0' || s[i] > '9') {
           s[j] = s[i];
           j++;
        }
    return j;
}
int main() {
    char s[SIZE];
    int len, i;
    cin.getline(s, sizeof(s));
    len = delnum(s);
    for (i = 0; i < len; i++)
       cout << s[i];
    cout << endl;
    return 0;
}

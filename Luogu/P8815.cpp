#include <bits/stdc++.h>
using namespace std;
stack<int> NumberStack;
stack<char> OperatorStack;
struct Node
{
    int Father;
    int Value;
    int LeftChild;
    int RightChild;
} List[100000];
int ListSize;
string s;
int main()
{
    cin >> s;
    int Last = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] == '0' || s[i] == '1')
            List[ListSize++].Value = s[i];
        else
        {
            OperatorStack.push(s[i]);
        }
    }
    return 0;
}

// 0 & (1 | 0) | (1 | 1 | 1 & 0);
// (0 & (1 | 0)) | ((1 | 1) | (1 & 0));
// 010|&11|10&||
// 括号内先算，从左向右，&优先于|，

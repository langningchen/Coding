#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <string.h>
#include <math.h>
using namespace std;
long long pad[75] = {0};
int length_pad = 0;

bitset<32> Kt[4] = {0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6};
bitset<32> Ht[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};

// Ft函数
bitset<32> Ft(int t, bitset<32> B, bitset<32> C, bitset<32> D)
{
    if (0 <= t && t <= 19)
    {
        return ((B & C) | ((~B) & D));
    }
    else if (20 <= t && t <= 39)
    {
        return (B ^ C ^ D);
    }
    else if (40 <= t && t <= 59)
    {
        return ((B & C) | (B & D) | (C & D));
    }
    else if (60 <= t && t <= 79)
    {
        return (B ^ C ^ D);
    }
    return 0;
}

//字符串的拓展函数
void SHA_PAD(string x)
{
    long long l = x.length();
    long long i = 0;
    pad[i] = 128;
    i++;
    l += 1;
    if ((l * 8) % 512 != 448)
    {
        for (; (l * 8) % 512 != 448; l++)
        {
            i++;
        }
    }
    l = x.length();
    l = l * 8;
    int a = 1;
    pad[i + 7] = l % 256;
    while (l / 256 > 0)
    {
        l = l / 256;
        pad[i + 7 - a] = l % 256;
        a++;
    }
    for (; a < 8; a++)
    {
        pad[i + 7 - a] = 0;
    }
    length_pad = i + 7;
}

//循环左移函数
bitset<32> ROTL(int s, bitset<32> W)
{
    bitset<32> m = W << s;
    for (int i = 0; i < s; i++)
    {
        m[i] = W[32 - s + i];
    }
    return m;
}

//模2^32加函数
bitset<32> ADD(bitset<32> a, bitset<32> b)
{
    bitset<32> c;
    int d = 0;
    for (int i = 0; i < 32; i++)
    {
        c[i] = (a[i] + b[i] + d) % 2;
        if (a[i] + b[i] + d >= 2)
        {
            d = 1;
        }
        else if (a[i] + b[i] + d < 2)
        {
            d = 0;
        }
    }
    return c;
}

//循环体
void DO(bitset<512> M)
{
    bitset<32> Wt[80] = {0};
    for (int i = 0; i < 16; i++)
    {
        for (int n = 0; n < 32; n++)
        {
            Wt[i][n] = M[(15 - i) * 32 + n];
        }
    }
    for (int t = 16; t <= 79; t++)
    {
        Wt[t] = ROTL(1, Wt[t - 3] ^ Wt[t - 8] ^ Wt[t - 14] ^ Wt[t - 16]);
    }
    bitset<32> A = Ht[0];
    bitset<32> B = Ht[1];
    bitset<32> C = Ht[2];
    bitset<32> D = Ht[3];
    bitset<32> E = Ht[4];
    for (int t = 0; t <= 79; t++)
    {
        bitset<32> temp = ADD(ADD(ADD(ROTL(5, A), Ft(t, B, C, D)), ADD(E, Wt[t])), Kt[t / 20]);
        E = D;
        D = C;
        C = ROTL(30, B);
        B = A;
        A = temp;
    }
    Ht[0] = ADD(Ht[0], A);
    Ht[1] = ADD(Ht[1], B);
    Ht[2] = ADD(Ht[2], C);
    Ht[3] = ADD(Ht[3], D);
    Ht[4] = ADD(Ht[4], E);
}
string SHA1(string Input)
{
    memset(pad, 0, sizeof(pad));
    length_pad = 0;
    Kt[0] = 0x5A827999;
    Kt[1] = 0x6ED9EBA1;
    Kt[2] = 0x8F1BBCDC;
    Kt[3] = 0xCA62C1D6;
    Ht[0] = 0x67452301;
    Ht[1] = 0xEFCDAB89;
    Ht[2] = 0x98BADCFE;
    Ht[3] = 0x10325476;
    Ht[4] = 0xC3D2E1F0;
    SHA_PAD(Input);
    size_t l = 0;
    //循环体
    while (l < Input.length())
    {
        size_t i = l;
        string Sx;
        for (; (i < 64 + l) && (i < Input.length()); i++)
        {
            bitset<8> mark = int(Input[i]);
            Sx += mark.to_string();
        }
        l += 64;
        if (i == Input.length())
        {
            if (length_pad <= 63)
                for (int n = 0; n <= length_pad; n++)
                {
                    bitset<8> mark = pad[n];
                    Sx += mark.to_string();
                }
            else
            {
                int n = 0;
                for (; i < l; i++)
                {
                    bitset<8> mark = pad[n];
                    n++;
                    Sx += mark.to_string();
                }
                bitset<512> Mx(Sx);
                DO(Mx);
                string last_Sx;
                for (; n <= length_pad; n++)
                {
                    bitset<8> mark = pad[n];
                    last_Sx += mark.to_string();
                }
                bitset<512> last_Mx(last_Sx);
                DO(last_Mx);
                break;
            }
        }
        bitset<512> Mx(Sx);
        DO(Mx);
    }

    stringstream sstream;
    for (int i = 0; i < 5; i++)
    {
        string s = Ht[i].to_string();
        for (int n = 0; n < 32;)
        {
            int result = 0;
            for (int m = 0; m < 4; m++)
            {
                result += (s[n + m] - '0') * pow(2, 3 - m);
            }
            sstream << hex << result;
            n += 4;
        }
    }
    return sstream.str();
}

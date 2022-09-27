#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#define ull unsigned long long int

//Pasinaudosiu SHA-256 algoritmo idėjomis

int countDigit(long long n)
{
    if (n == 0)
        return 1;
    int count = 0;
    while (n != 0) {
        n = n / 10;
        ++count;
    }
    return count;
}

string decToBinary(int N)
{
    // To store the binary number
    ull B_Number = 0;
    int cnt = 0;
    while (N != 0) {
        int rem = N % 2;
        ull c = pow(10, cnt);
        B_Number += rem * c;
        N /= 2;
        // Count used to store exponent value
        cnt++;
    }
    string bin=to_string(B_Number);
    if (countDigit(B_Number) < 8)
    {
        for (int i = 0; i < 8 - countDigit(B_Number); i++)
        {
            bin = "0" + bin;
        }
    }
    return bin;
}

void reverseArray(string &arr, int start, int end)
{
    while (start < end)
    {
        std::swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

/* Function to right rotate arr[]
of size n by d */
void rightRotate(string &arr, int d, int n)
{
    reverseArray(arr, 0, n - 1);
    reverseArray(arr, 0, d - 1);
    reverseArray(arr, d, n - 1);
}

void rightShift(string& arr, int d)
{
    for (int i = 0; i < d; i++)
    {
        arr = "0" + arr;
        arr.pop_back();
    }
}

string XOR(string a, string b, string c)
{
    string temp="";
    for (int i = 0; i < 32; i++)
    {
        if ((int)a[i] + (int)b[i] + (int)c[i] ==1 || (int)a[i] + (int)b[i] + (int)c[i] == 3)
        {
            temp += "1";
        }
        else
        {
            temp += "0";
        }
    }
    return temp;
}

int main()
{
    string text;
    getline(cin,text);
    vector <string> binar;
    for (int i = 0; i < text.length(); i++)
    {
        binar.push_back(decToBinary((int)text[i]));
    }
    binar.push_back("10000000");
    
    int multipleOf512=0;
    while (binar.size()*8 > multipleOf512)
    {
        multipleOf512 += 512;
    }

    for (int i = binar.size()*8; i < multipleOf512 - 64; i+=8)
    {
        binar.push_back("00000000");
    }

    string bincount = decToBinary(text.length()*8);
    int bcount = bincount.length();
    for (int i = 0; i < 64 - bcount; i++)
    {
        bincount = "0" + bincount;
    }
    string temp = "";
    for (int i = 0; i < 8; i++)
    {
        for (int j = i * 8; j < (i+1)*8; j++)
        {
            temp += bincount[j];
        }
        binar.push_back(temp);
        temp = "";
    }

    for (int i = 0; i < binar.size(); i++)
    {
        cout << binar[i] << " ";
        if ((i + 1) % 8 == 0)
        {
            cout << endl;
        }
    }

    //---
    uint32_t h[8];
    h[0] = 0x6a09e667;
    h[1] = 0xbb67ae85;
    h[2] = 0x3c6ef372;
    h[3] = 0xa54ff53a;
    h[4] = 0x510e527f;
    h[5] = 0x9b05688c;
    h[6] = 0x1f83d9ab;
    h[7] = 0x5be0cd19;

    const unsigned int k[64] = //UL = uint32
    { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
     0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
     0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
     0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
     0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
     0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
     0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
     0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
     0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
     0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
     0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
     0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
     0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
     0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
     0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
     0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };

    vector <string> w;
    string temp1 = "", temp2 = "", temp3 = "", s0 = "", s1 = "";
    for (int i = 0; i < multipleOf512 / 512; i++)
    {
        temp = "";
        for (int j = 0; j < 16; j++)
        {
            for (int o = 0; o < 4; o++)
            {
                temp += binar[j * 4 + o];
           }
            w.push_back(temp);
            temp = "";
        }
        for (int j = 0; j < 48; j++)
        {
            w.push_back("00000000000000000000000000000000");
        }
        for (int j = 16; j < 64; j++)
        {
            temp1 = w[j - 15];
            rightRotate(temp1, 7, 32);
            temp2 = w[j - 15];
            rightRotate(temp2, 18, 32);
            temp3 = w[j - 15];
            rightShift(temp3, 3);
            s0 = XOR(temp1, temp2, temp3);
        }

        

    }
    /*for (int i = 0; i < w.size(); i++)
    {
        cout << w[i] << " ";
        if ((i + 1) % 2 == 0)
        {
            cout << endl;
        }
    }*/

}


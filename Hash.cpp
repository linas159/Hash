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
}


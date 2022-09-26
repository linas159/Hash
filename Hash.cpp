#include <iostream>
#include <cmath>
#include <string>
using namespace std;

#define ull unsigned long long int

//Pasinaudosiu SHA-256 algoritmo idėjomis

int decToBinary(int N)
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
    return B_Number;
}

int main()
{
    string text;
    getline(cin,text);
    for (int i = 0; i < text.length(); i++)
    {
        cout<<decToBinary((int)text[i])<<" ";
    }

}


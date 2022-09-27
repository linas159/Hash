#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void fromFile(string fileName)
{
    ifstream in(fileName);
}

void hashingSeed(unsigned long long int& hash, string text)
{
    for (int i = 0; i < text.size(); i++)
    {
        hash += text[i]*(i+1)*(text[i]%31+1);
    }

}

string toHex(unsigned long long int n)
{
    // char array to store hexadecimal number
    char hexaDeciNum[100];

    // counter for hexadecimal number array
    int i = 0;
    while (n != 0) {
        // temporary variable to store remainder
        int temp = 0;

        // storing remainder in temp variable.
        temp = n % 16;

        // check if temp < 10
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }

        n = n / 16;
    }
    string a = "";
    // printing hexadecimal number array in reverse order
    for (int j = i - 1; j >= 0; j--)
        a = hexaDeciNum[j] + a;
    return a;
}

string to256bit(unsigned long long int hash)
{
    stringstream hs;
    for (int i = 2; i < 99; i++)
    {
        if (hs.str().size() > 64)
        {
            break;
        }
        hs << toHex((hash * i));
    }
    return hs.str().substr(0,64);
}

int main()
{
    cout << "Ar norite irasyti ranka? Y/N";
    char a;
    cin >> a;
    string text, hashcode;
    unsigned long long int hash = 1;
    if (a == 'y' || a == 'Y')
    {
        cin >> text;
        hashingSeed(hash, text);
        hashcode = to256bit(hash);
        cout << hashcode;
    }
    

}


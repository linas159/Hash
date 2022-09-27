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
    for (int i = 1; i <= text.size(); i++)
    {
        hash += text[i]*i;
    }

}

string to256bit(unsigned long long int hash)
{
    stringstream hs;
    int k = 2;
    while (hs.str().size() < 64)
    {
        hs << (hash ^ k);
        k++;
    }
    return hs.str();
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


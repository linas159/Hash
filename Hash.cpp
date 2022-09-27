#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void fromFile(string fileName)
{
    ifstream in(fileName);
}

void hashing(unsigned long long int& hash, string text)
{
    for (int i = 1; i <= text.size(); i++)
    {
        hash += text[i]*i;
    }
    
}

int main()
{
    cout << "Ar norite irasyti ranka? Y/N";
    char a;
    cin >> a;
    string text;
    unsigned long long int hash = 1;
    if (a == 'y' || a == 'Y')
    {
        cin >> text;
        hashing(hash, text);
        cout << hash;
    }
    

}


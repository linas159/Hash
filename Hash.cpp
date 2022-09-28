#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <chrono>

using namespace std;

string fromFile(string fileName)
{
    string text;
    ifstream in(fileName);
    in >> text;
    return text;
}

void hashingSeed(unsigned long long int& hash, string text)
{
    hash = 1;
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

string random_string(string::size_type length)
{
    static auto& chrs = "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static mt19937 rg{ random_device{}() };
    thread_local static uniform_int_distribution<string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    s.reserve(length);

    while (length--)
        s += chrs[pick(rg)];

    return s;
}

int main()
{
    cout << "Ar norite irasyti ranka? Y/N";
    char a;
    cin >> a;
    string text, hashcode;
    unsigned long long int hash;
    if (a == 'y' || a == 'Y')
    {
        cin >> text;
        hashingSeed(hash, text);
        hashcode = to256bit(hash);
        //cout << hashcode;
    }
    else
    {
        cout << "Ar norite sugeneruoti naujus failus? Y/N";
        cin >> a;
        if (a == 'y' || a == 'Y')
        {
            ofstream out ("1char1.txt");
            out << random_string(1);
            out.close();
            ofstream out1("1char2.txt");
            out1 << random_string(1);
            out1.close();
            ofstream out2("daugRand1.txt");
            out2 << random_string(1500);
            out2.close();
            ofstream out3("daugRand2.txt");
            out3 << random_string(2000); 
            out3.close();

            string s= random_string(2000);
            s[1000] = 'a';
            ofstream out4("daugNeRand1.txt");
            out4 << s;
            out4.close();
            s[1000] = 'z';
            ofstream out5("daugNeRand2.txt");
            out5 << s;
            out5.close();

        }
        cout << "Ar norite istestuoti failus? Y/N";
        cin >> a;
        if (a == 'y' || a == 'Y')
        {
            while (1 > 0)
            {
                cout << "Iveskite failo pavadinima:";
                string fileName;
                cin >> fileName;
                text = fromFile(fileName);
                hashingSeed(hash, text);
                hashcode = to256bit(hash);
                cout << hashcode << endl;
                cout << "Ar norite kartoti? Y/N"<<endl;
                cin >> a;
                if (a == 'n' || a == 'N')
                {
                    break;
                }
            }
            
        }
        cout << "Ar norite istirti hash funkcijos efektyvuma? Y/N";
        cin >> a;
        if (a == 'y' || a == 'Y')
        {
            ifstream in1("konstitucija.txt");
            int k = 0, nextLine = 2;
            stringstream text1;
            string textLine;
            while (!in1.eof())
            {
                k++;
                getline(in1, textLine);
                //cout << textLine<<endl;
                text1 << textLine;
                if (k == nextLine)
                {
                    nextLine *= 2;
                    auto t_start = std::chrono::high_resolution_clock::now();
                    //cout << text1.str() << endl;
                    hashingSeed(hash, text1.str());
                    hashcode = to256bit(hash);
                    auto t_end = std::chrono::high_resolution_clock::now();

                    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
                    cout << hashcode << endl;
                    cout << k << " eiluciu uztruko: " << elapsed_time_ms<<endl;
                }
            }
        }
        cout << "Ar norite sugeneruoti 100000 poru? Y/N";
        cin >> a;
        if (a == 'y' || a == 'Y')
        {
            ofstream out("100000poru.txt");
            for (int i = 0; i < 100000; i++)
            {
                if (i < 25000)
                {
                    out << random_string(10)<<" "<< random_string(10)<<endl;
                }
                else if (i < 50000)
                {
                    out << random_string(100)<<" "<< random_string(100) << endl;
                }
                else if (i < 75000)
                {
                    out << random_string(500)<<" "<< random_string(500) << endl;
                }
                else
                {
                    out << random_string(1000)<<" "<< random_string(1000) << endl;
                }
            }
        }
        cout << "Ar norite istirti 100000 poru panasuma? Y/N";
        cin >> a;
        if (a == 'y' || a == 'Y')
        {
            ifstream in("100000poru.txt");
            string hashcode1;
            int k = 0;
            for (int i = 0; i < 100000; i++)
            {
                in >> text;
                hashingSeed(hash, text);
                hashcode = to256bit(hash);
                cout << hashcode << " ";
                in >> text;
                hashingSeed(hash, text);
                hashcode1 = to256bit(hash);
                cout << hashcode1 << endl;
                if (hashcode == hashcode1)
                {
                    k++;
                }
            }
            cout << endl << "Hashas pasikartojo: " << k << " kartu" << endl;
        }
        cout << "Ar norite sugeneruoti 100000 poru kurios skiriasi tik vienu simboliu? Y/N";
        cin >> a;
        if (a == 'y' || a == 'Y')
        {
            ofstream out("100000poru2.txt");
            string word;
            for (int i = 0; i < 100000; i++)
            {
                if (i < 25000)
                {
                    word = random_string(10);
                    word[0] = 'a';
                    out << word << " ";
                    word[0] = 'z';
                    out << word << endl;
                }
                else if (i < 50000)
                {
                    word = random_string(100);
                    word[0] = 'a';
                    out << word << " ";
                    word[0] = 'z';
                    out << word << endl;
                }
                else if (i < 75000)
                {
                    word = random_string(500);
                    word[0] = 'a';
                    out << word << " ";
                    word[0] = 'z';
                    out << word << endl;
                }
                else
                {
                    word = random_string(1000);
                    word[0] = 'a';
                    out << word << " ";
                    word[0] = 'z';
                    out << word << endl;
                }
            }
        }
        cout << "Ar norite istirti 100000 poru skirtinguma procentiskai? Y/N";
        cin >> a;
        if (a == 'y' || a == 'Y')
        {

        }
    }

}


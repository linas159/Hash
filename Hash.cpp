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

string HexToBin(string hexdec)
{
    long int i = 0;
    stringstream hs;
    while (hexdec[i]) {

        switch (hexdec[i]) {
        case '0':
            hs << "0000";
            break;
        case '1':
            hs << "0001";
            break;
        case '2':
            hs << "0010";
            break;
        case '3':
            hs << "0011";
            break;
        case '4':
            hs << "0100";
            break;
        case '5':
            hs << "0101";
            break;
        case '6':
            hs << "0110";
            break;
        case '7':
            hs << "0111";
            break;
        case '8':
            hs << "1000";
            break;
        case '9':
            hs << "1001";
            break;
        case 'A':
        case 'a':
            hs << "1010";
            break;
        case 'B':
        case 'b':
            hs << "1011";
            break;
        case 'C':
        case 'c':
            hs << "1100";
            break;
        case 'D':
        case 'd':
            hs << "1101";
            break;
        case 'E':
        case 'e':
            hs << "1110";
            break;
        case 'F':
        case 'f':
            hs << "1111";
            break;
        default:
            cout << "\nInvalid hexadecimal digit "
                << hexdec[i];
        }
        i++;
    }
    return hs.str();
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
        cout << hashcode;
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
                    cout << k << " eiluciu uztruko: " << elapsed_time_ms << " ms" << endl;
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
            ifstream in("100000poru2.txt");
            string hashcode1;
            int k = 0;
            float hexMin = 100, hexMax = 0, hexAvg = 0, bitMin = 100, bitMax = 0, bitAvg = 0, perc;
            for (int i = 0; i < 100000; i++)
            {
                in >> text;
                hashingSeed(hash, text);
                hashcode = to256bit(hash);
                //cout << hashcode << " ";
                in >> text;
                hashingSeed(hash, text);
                hashcode1 = to256bit(hash);
                //cout << hashcode1 << endl;
                for (int i = 0; i < 64; i++)
                {
                    if (hashcode[i] == hashcode1[i])
                    {
                        k++;
                    }
                }
                perc = (float)k / 64 * 100;
                //cout << perc << endl;
                k = 0;
                hexAvg += perc;
                if (hexMin > perc)
                {
                    hexMin = perc;
                }
                if (hexMax < perc)
                {
                    hexMax = perc;
                }

                hashcode = HexToBin(hashcode);
                hashcode1 = HexToBin(hashcode1);
                for (int i = 0; i < hashcode.length(); i++)
                {
                    if (hashcode[i] == hashcode1[i])
                    {
                        k++;
                    }
                }
                perc = (float)k / hashcode.length() * 100;
                //cout << perc << endl;
                k = 0;
                bitAvg += perc;
                if (bitMin > perc)
                {
                    bitMin = perc;
                }
                if (bitMax < perc)
                {
                    bitMax = perc;
                }
            }
            hexAvg = hexAvg / 100000;
            bitAvg = bitAvg / 100000;

            cout << endl;
            cout << "Minimumas Bitu lygmenyje: " << bitMin << endl;
            cout << "Vidurkis Bitu lygmenyje: " << bitAvg << endl;
            cout << "Maksimumas Bitu lygmenyje: " << bitMax << endl;
            cout << endl;
            cout << "Minimumas Hexu lygmenyje: " << hexMin << endl;
            cout << "Vidurkis Hexu lygmenyje: " << hexAvg << endl;
            cout << "Maksimumas Hexu lygmenyje: " << hexMax << endl;
        }
    }

}


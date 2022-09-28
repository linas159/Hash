# Hash kodo generavimas

## Programos pseudocode

```
1. funkcija fromFile: leidžia nuskaityti informaciją iš failo.
2. funkcija hashingSeed: sugeneruoja kiekvienai frazei skirtingą "sėklą".
3. funkcija toHex: paverčia dešimtainį skaičių į šešioliktainį.
4. funkcija to256bit: sugeneruotą išskirtinę sėklą paverčia į 64 simbolių kodą.
5. funkcija random_string: sugeneruoja pasirinkto ilgio atsitiktinį žodį.
6. funkcija HexToBin: iš šešioliktainio skaičiaus padaro dvejetainį.
7. funkcija byHand: leidžia vartotojui naudojantis interface'u pačiam įrašyti pasirinktą žodį ir jį užkoduoti
8. funkcija fileGen: sugeneruoja failus (Bent du failai būtų sudaryti tik iš vieno, tačiau skirtingo, simbolio.
Bent du failai būtų sudaryti iš daug (> 1000) atsitiktinai sugeneruotų simbolių.
Bent du failai būtų sudaryti iš daug (> 1000) simbolių, bet skirtųsi vienas nuokito tik vienu (pvz. vidurinėje pozicijoje esančiu) simboliu.
Tuščio failo)
9. funkcija testTheFiles: Ištestuoja aukščiau pateiktus failus, t. y. nuskaito vartotojo pasirinkto failo zodį ir jį užkoduoja.
10. funkcija efect: Išmatuoja hashavimo greitį pasinaudojant pateiktu failu konstitucija.txt
11. funkcija generatingPairs: Sugeneruoja 100000 skirtingų porų žodžių iš atsitiktinių simbolių.
12. funkcija similarity: Užkoduojami aukščiau pateikto failo žodžiai ir skaičiuojama kiek kartų poros pasikartoja
13. funkcija void generatingNotRandPairs: Sugeneruoja 100000 porų žodžių iš atsitiktinių simbolių, kurios skiriasi tik vienu simboliu.
14. funkcija differences: Tikrina kiek procentiškai skiriasi aukščiau aprašyti failo užkoduoti duomenys šešioliktainiame ir dvejetainiame lygmenyje
15. main funkcija: Klausia vartotojo kokią užduotį turi įvykdyti programa.
```

## Testavimas

## Naudotojo įrašyto žodžio testavimas:

![image](https://user-images.githubusercontent.com/93277316/192835352-495fe0e4-2b17-49c9-bab6-2149ba2f1535.png)


### 1-3 reikalavimų testavimas:
![image](https://user-images.githubusercontent.com/93277316/192834393-649b9db8-cf90-4c63-a27c-85a7f0f35d9f.png)

Matome, kad hash kodas yra visada tokio pat dydžio, taip pat matome ir lavinos efektą.

## Efetyvumo tyrimas:

![image](https://user-images.githubusercontent.com/93277316/192835779-9fef1e2a-e716-47ed-8e82-ac1bde0271a7.png)

Matome, kad užkoduoti pavyko milisekunžių greičiu.

## Atsparumo kolizijai tyrimas:

![image](https://user-images.githubusercontent.com/93277316/192836664-85370fbe-c18f-4c4d-b520-b3d005e73d89.png)

Programa atspari kolizijai.

## Lavinos efekto tyrimas:

![image](https://user-images.githubusercontent.com/93277316/192837459-bb0f6f5e-7df2-46b2-864a-a47c298afb1d.png)

Matome, kad lavinos efektas yra, tačiau jį būtų galima patobulinti.

## Išvados

Programa užduotį įvykdo sklandžiai ir gana efektyviai, tačiau lavinos efekto tobulinimui ribų nėra.

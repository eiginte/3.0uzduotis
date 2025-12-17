CPU: Intel Core i5-10210U, 10-oji karta, 4 branduoliai / 8 gijos, 1.6 GHz bazinis dažnis (iki ~4.2 GHz Turbo)
RAM: 16 GB DDR4-2400 MHz (2 × 8 GB, Hynix)
SSD: 512 GB Lexar NM620 PCIe NVMe SSD

-------------3.0 versija-----------------

Šioje versijoje parengtas diegimo failas StudentuRusiavimas_Setup.exe
Atsisiųskite šį failą, tuomet paleiskite jį:
<img width="800" height="614" alt="image" src="https://github.com/user-attachments/assets/9b7989e0-8c4f-4b29-8f80-3bf24aacd894" />
Tuomet spauskite Next, ir Install
Jūsų Desktop'e turėtų susikurti programa pavadinimu "StudentuRusiavimas", ją taip pat galite rasti ir šiuo adresu: C:\Program Files\VU\Eiginte-Smigelskyte
Paleiskite ją administratoriaus teisėmis ir pasirinkite nuorimus parametrus (apačioje, prie 2.0 versijos yra instrukcija kaip naudotis programa)
Jei norite nuskaityti iš failo galite rinktis šiuos: 5_stud.txt arba 1000_stud.txt (jie automatiškai buvo įdiegti su programa).
Tuomet C:\Program Files\VU\Eiginte-Smigelskyte aplanke rasite suskirstytus studentus, t.y. vargsiukai.txt bei kietiakai.txt failus.
Norėdami ištrinti programa, atsidarykite tą patį aplanką (C:\Program Files\VU\Eiginte-Smigelskyte) ir paspauskite "unins000.exe", tuomet visi prieš tai įdiegti failai bus ištrinti iš jūsų kompiuterio.


-------------2.0 versija:----------------

Programos naudojimosi instrukcija:
Programa leidžia kurti studentų grupes, pridėti studentus, rikiuoti juos pagal vardą arba pavardę ir saugoti į failus.

Failai:
main.cpp – pagrindinis programos failas
Studentas.h/cpp – studento klasė su vardu, pavarde, pažymiais ir egzamino balu
StudentuGrupe.h/cpp – studentų grupės klasė su funkcijomis pridėjimui, skaitymui, generavimui ir rikiavimui
Zmogus.h – bendroji klasė, iš kurios paveldi Studentas

Kompiliavimas:
Naudojant CMakeLists.txt:
Sukurkite build aplanką:
mkdir build
cd build

Sugeneruokite build failus:
cmake ..

Sukompiliuokite programą:
cmake --build . --config Release

Paleiskite vykdomąjį failą:
.\Release\studentai.exe

Tuomet:
Galime pasirinkti strategiją, pagal kurią bus skirstomi studentai:
<img width="1226" height="169" alt="image" src="https://github.com/user-attachments/assets/c9db59fc-1f8f-43fc-841e-7d1553eac757" />
Tuomet pasirenkame norimą konteinerį:
<img width="1189" height="124" alt="image" src="https://github.com/user-attachments/assets/82451e3c-0ce6-4deb-81e5-80b5785838b2" />
Tuomet pasirenkame veiksmą (pvz. nuskaityti iš failo):
<img width="603" height="779" alt="image" src="https://github.com/user-attachments/assets/92c113a7-1da5-47c5-9b6d-76ca913c61dc" />
tada renkames, pagal ką norime skirstyti, ir ar norime surikiuoti studentus pagal pavardę:
<img width="816" height="862" alt="image" src="https://github.com/user-attachments/assets/a3481b66-b5ad-4436-bc0f-d4f690474318" />
Tuomet išrūšiuoti studentai yra įrašomi į failus vargsiukai.txt bei kietiakai.txt



Testavimas atliktas su Google Test biblioteka
Testai aprašomi daile test.cpp. Naudojamos dvi testų grupės (test suites):
"StudentuGrupeTests" testuoja "StudentuGrupe" struktūros f-jos tikrina studentų pridėjimą į grupę ("prideti_studenta"), ar studentas tinkamai įrašomas į vektorių ir ar jo vardas bei pavardė teisingai saugomi.
"StudentasTestas" tikrina studentų rikiavimą pagal pavardę ("RikiuojaPagalPavarde"), tikrina studentų rikiavimą pagal vardą ("RikiuojaPagalVardą").
Išjungtas konstruktorių/destruktorių logavimas, testo "main" funkcijoje "std::cout" nukreipiamas į "nullptr", kad testų metu nebūtų matomi konstruktoriai, kopijavimo ar destruktorių pranešimai. Tai padeda išlaikyti testų rezultatų konsolės išvestį švarią.

Kompiliavimas (Windows pavyzdys su g++):
g++ -std=c++17 test.cpp Studentas.cpp StudentuGrupe.cpp googletest/src/gtest-all.cc -I googletest/include -I googletest -o tests.exe

ir tada paleidžiame testus:
.\tests.exe

gauname:
<img width="1906" height="491" alt="image" src="https://github.com/user-attachments/assets/99f18001-22d6-4939-aa36-a32f1e86fe57" />



-------------1.5 VERSIJA-----------------------
Vietoj klasės Studentas sukurtos dvi klasės, bazinė abstrakti klasė Zmogus, kurioje aprašome žmogų (t.y. vardą ir pavardę) ir iš jos sukūrėmė išvestinę klasę Studentas, kuroje liko likusieji dalykai, kaip 1.2 versijoje Studentas klasėje.

Bazinė klasė Zmogus padaryta abstrakčia, nes turi gryną virtualią funkciją isvesti(), dėl to tiesiogiai sukurti Zmogus objekto neįmanoma – galima kurti tik iš jos paveldėtas klases, pvz., Studentas, kurios įgyvendina šią funkciją.

DEMONSTRACIJA:
Demonstracijoje parodyta, kad bandymas sukurti tiesioginį Zmogus objektą būtų neįmanomas
(negalime kompiliuoti),
<img width="1294" height="400" alt="image" src="https://github.com/user-attachments/assets/752a9c65-1c55-407a-b647-8ce7868a2a47" />

o vietoj to sukuriamas Studentas objektas, kuris paveldi iš Zmogus ir įgyvendina abstrakčią funkciją isvesti(). Tai vizualiai parodo, kad bazinė klasė veikia kaip abstrakti.
<img width="1322" height="190" alt="image" src="https://github.com/user-attachments/assets/d6f2dbc1-64c6-4664-8e8c-e454a7ae056b" />


----------------------v1.2 --------------------
Kodas nepraranda savo funkcijų, yra naudojama rule of 3.

Duomenų įvestis:

rankiniu būdu - Naudotojas tiesiogiai įveda studento vardą, pavardę, namų darbų pažymius ir egzamino balą per konsolę (cin). Kiekvienam studentui sukuriamas laikinas objektas Studentas s, užpildomas duomenimis, tada dedamas į grupę (grupe.prideti_studenta(s)).
<img width="806" height="812" alt="image" src="https://github.com/user-attachments/assets/8a0cd48e-bc60-4432-b416-8af4f73617f4" />




automatiniu - Metodas StudentuGrupe::generuoti_studentus(int kiek, int nd_sk) sugeneruoja atsitiktinius studentus. Studentai su random vardais/pavardėmis ir namų darbų pažymiais yra įdedami į grupę.
<img width="854" height="593" alt="image" src="https://github.com/user-attachments/assets/2a832d82-cdf1-4332-8e55-f2f015291d00" />


iš failo - Metodas StudentuGrupe::skaityti_is_failo(const std::string& failas) skaito studentų duomenis CSV ar txt formato failo eilutėmis. Kiekviena eilutė interpretuojama per Studentas::readStudent(std::istream&).

<img width="929" height="940" alt="image" src="https://github.com/user-attachments/assets/078310f3-8f40-4dee-99a4-833ea9552c19" />

<img width="785" height="439" alt="image" src="https://github.com/user-attachments/assets/fdf583a9-fa24-4023-9f7a-6d1853e511d6" />


Studentas turi konstruktorius su skirtingais parametrais:
Studentas() – tuščias studentas;
Studentas(const std::string&, const std::string&, const std::vector<int>&, int) – parametrizuotas;
Studentas(std::istream&) – įvedimas iš srauto.

Duomenų išvestis:
į failą: 
StudentuGrupe turi du perdengtus metodus irasyti_i_faila:
  irasyti_i_faila(const std::vector<Studentas>&, const std::string&) – išveda į failą, kai studentai saugomi vector konteineryje;
  irasyti_i_faila(const std::list<Studentas>&, const std::string&) – išveda į failą, kai studentai saugomi list konteineryje.

Išvestis į ekraną:
Ekrane rodomi tik svarbiausi pranešimai, pvz.:
[DEFAULT CTOR] Sukurtas tuscias studentas
[COPY CTOR] Kopijuojamas studentas: ...
[DESTRUCTOR] Naikinamas studentas: ...


-------------------v1.1-------------------

Išlaikytos visos funkcijos kode, pakeista Studentas struct į class.

------------TREČIOJI STRATEGIJA-------------

------NAUDOJAME O1:----------

NAUDOJANT STRUCT:
.exe failo dydis: 3 078 KB

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000000         | vector      | 1.68749 | 2.59365 | 1.28271 | 5.56384 |
|                 |             | 1.78919 | 2.43517 | 1.27425 | 5.49861 |
|                 |             | 2.23562 | 3.15794 | 1.29675 | 6.69031 |
|                 | Vidurkis:   |    1.90410      |    2.72892     |    1.28457   | 5.91759   |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000000        | vector      |  18.3211 | 28.4613 | 15.6255 | 62.4079 |
|                 |             | 18.4279 | 28.4746 | 13.9341 | 60.8366 |
|                 |             | 18.914 | 25.9794 | 14.3592 | 59.2526 |
|                 | Vidurkis:   |    18.55433  |   27.63843   |    14.63960   |   60.83237 |



NAUDOJANT CLASS:
.exe failo dydis: 3 040KB

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000000         | vector      | 1.67366 | 2.44873 | 1.5246 | 5.64699 |
|                 |             | 1.69991 | 3.14393 | 2.29189 | 7.13574 |
|                 |             | 1.711 | 3.11107 | 1.73976 | 6.56183 |
|                 | Vidurkis:   |    1.69486      |    2.90124     |     1.85208  |  6.44819  |


| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000000        | vector      | 19.9899 | 30.6339 | 18.095 | 68.7189 |
|                 |             | 18.6978 | 32.731 | 23.4585 | 74.8873 |
|                 |             | 18.1406 | 31.4803 | 18.4652 | 68.0861 |
|                 | Vidurkis:   |    18.94277      |    31.61507  |   20.00623   |70.56410    |





------NAUDOJAME O2:----------

NAUDOJANT STRUCT:
.exe failo dydis: 3 076 KB

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000000         | vector      |  1.70842 | 2.43277 | 1.3315 | 5.47268 |
|                 |             |  1.74942 | 2.54638 | 1.64584 | 5.94164 |
|                 |             | 1.74459 | 2.34572 | 1.2929 | 5.38321 |
|                 | Vidurkis:   |   1.73414       |   2.44162      |    1.42341   |   5.59918 |


| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000000        | vector      |  18.523 | 27.1905 | 12.8776 | 58.5912 |
|                 |             | 17.592 | 25.0441 | 12.7843 | 55.4204 |
|                 |             | 17.8229 | 25.8738 | 12.9854 | 56.6822 |
|                 | Vidurkis:   |     17.9793     |    26.0361     |  12.8824     | 56.8979   |


NAUDOJANT CLASS:
.exe failo dydis: 3 032 KB

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000000         | vector      | 1.65237 | 2.47791 | 1.51089 | 5.64117 |
|                 |             |  1.79757 | 2.64162 | 1.53205 | 5.97123 |
|                 |             | 1.76506 | 2.53332 | 1.53867 | 5.83705 |
|                 | Vidurkis:   |    1.73833      |    2.55095     |  1.52720     | 5.81648   |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000000        | vector      |  18.0456 | 29.8032 | 18.8428 | 66.6916 |
|                 |             |   18.5116 | 27.097 | 15.4765 | 61.0851 |
|                 |             |  18.141 | 28.7953 | 16.328 | 63.2644 |
|                 | Vidurkis:   |   18.23273   |   28.56517   |  16.88243     | 63.68037   |


------NAUDOJAME O3:----------
NAUDOJANT STRUCT:

.exe failo dydis: 3 078 KB

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000000         | vector      | 1.71094 | 2.39865 | 1.38239 | 5.49198 |
|                 |             | 1.70075 | 2.28039 | 1.26789 | 5.24903 |
|                 |             | 1.76482 | 2.46221 | 1.35098 | 5.57801 |
|                 | Vidurkis:   |      1.72550    |    2.38042     |  1.33375     | 5.43967   |


| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000000        | vector      | 18.3108 | 29.3217 | 14.2749 | 61.9074 |
|                 |             | 17.9899 | 24.5798 | 12.5875 | 55.1573 |
|                 |             |  21.0871 | 24.9803 | 12.7384 | 58.8058 |
|                 | Vidurkis:   |     19.12927    |     26.29393    |  13.20027   |  58.6235  |


NAUDOJANT CLASS:
.exe failo dydis: 3 066 KB

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000000         | vector      | 1.6965 | 2.48255 | 1.62096 | 5.80001 |
|                 |             | 1.65972 | 2.41078 | 1.52702 | 5.59752 |
|                 |             | 2.67258 | 3.92559 | 1.715 | 8.31316 |
|                 | Vidurkis:   |   2.00960       |  2.93964       |  1.62099     |   6.57023 |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000000        | vector      |  20.9964 | 25.5148 | 15.1108 | 61.622 |
|                 |             | 24.6157 | 26.505 | 15.1676 | 66.2883 |
|                 |             | 24.0875 | 26.0397 | 15.1634 | 65.2906 |
|                 | Vidurkis:   |     23.2332 |   26.0198   | 15.1473      |  64.4003  |




-----------------v1.0------------------


-----------PIRMOJI STRATEGIJA----------------                                                                        

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000            | vector      | 0.0068874       | 0.0111862      | 0.0079608    | 0.0260344 |
|                 |             | 0.0069878       | 0.0117141      | 0.0071147    | 0.0258166 |
|                 |             | 0.0092995       | 0.0086578      | 0.006482     | 0.0244393 |
|                 | Vidurkis:   | 0.0077249       | 0.0105194      | 0.0071858    | 0.0254301 |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000            | list        |   0.0387605     |    0.0127571   |  0.0072493   | 0.0587669 |
|                 |             |   0.0068473     |    0.0068644   |  0.0029917   | 0.0167034 |
|                 |             |   0.0080481     |    0.0101774   |  0.006378    | 0.0246038 |
|                 | Vidurkis:   |   0.0178853     |    0.00993297  |  0.0055397   | 0.0333579 |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000           | vector      |    0.0546293    |   0.0504718    |   0.0282506  | 0.133352  |
|                 |             |    0.056509     |   0.0673369    |   0.0673369  | 0.176206  |
|                 |             |    0.0502976    |   0.0433942    |   0.0286642  | 0.122356  |
|                 | Vidurkis:   |    0.05381197   |   0.0537343    |   0.0414172  | 0.1439713 |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000           | list        |    0.0864375    |  0.0411055     |  0.0296593   | 0.157202  |
|                 |             |    0.052016     |  0.0445162     |  0.0262295   | 0.122762  |
|                 |             |    0.0522222    |  0.0445154     |  0.0284577   | 0.125195  |
|                 | Vidurkis:   |    0.0635586    |  0.0433790     |   0.0281155  |  0.135053 |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 100000          | vector      |    0.387466     |    0.436989    |   0.308779   |  1.13323  |
|                 |             |    0.356367     |    0.47326     |   0.28659    |  1.11622  |
|                 |             |    0.373309     |    0.451625    |   0.281246   |  1.10618  |
|                 | Vidurkis:   |    0.3723807    |    0.453958    |   0.292205   | 1.1185433 |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 100000          | list        |    0.367664     |    0.429952    |  0.31559     |  1.11321  |
|                 |             |    0.363325     |    0.406695    |  0.256621    |  1.02664  |
|                 |             |    0.377361     |    0.410027    |  0.271714    |  1.0591   |
|                 | Vidurkis:   |    0.36945      |    0.415558    |  0.281308    |  1.066317 |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000000         | vector      |    3.40603      |    4.78379     |  2.91496     |  11.1048  |
|                 |             |    3.35895      |    4.91191     |  2.91655     |  11.1874  |
|                 |             |    3.28127      |    4.81852     |  2.8792      |  10.979   |
|                 | Vidurkis:   |    3.34875      |    4.8380733   |  2.90357     |  11.0904  |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000000         | list        |     3.4083      |    4.7713      |  2.58701     |  10.7666  |
|                 |             |     3.41845     |    4.63241     |  2.59352     |  10.6444  |
|                 |             |     3.33882     |    4.67643     |  2.51409     |  10.5293  |
|                 | Vidurkis:   |     3.3885233   |    4.69338     |  2.5648733   | 10.6467667|

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000000        | vector      |     65.9793     |    127.01      |   63.1259    |  256.115  |
|                 |             |     32.7915     |    114.271     |   57.118     |  204.18   |
|                 |             |     71.7807     |    117.247     |   53.6043    |  242.632  |
|                 | Vidurkis:   |     56.8505     |    119.5093    |   57.9494    |  234.309  |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000000        | list        |    79.2348      |    114.975     |   62.9844    |  257.195  |
|                 |             |    41.6277      |    59.3376     |   52.2333    |  153.199  |
|                 |             |    73.4312      |    101.914     |   60.0145    |  235.36   |
|                 | Vidurkis:   |    64.76457     |    92.07553    |   58.41073   |  215.2513 |

-------------ANTROJI STRATEGIJA-------------

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000            | vector      |        0.004949 |       0.009048 |     0.001013 |  0.015011 |
|                 |             |        0.012987 |       0.008178 |     0.006455 |  0.027619 |
|                 |             |        0.005557 |       0.010266 |     0.003445 |  0.019268 |
|                 | Vidurkis:   |        0.007831 |       0.009164 |     0.003638 |  0.020633 |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000            | list        |        0.017708 |       0.003772 |     0.007688 |  0.029168 |
|                 |             |        0.006560 |       0.006035 |     0.005465 |  0.018060 |
|                 |             |        0.015804 |       0.009652 |     0.003029 |  0.028484 |
|                 | Vidurkis:   |        0.013357 |       0.006486 |     0.005394 |  0.025237 | 

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000           | vector      |        0.161815 |       0.080491 |     0.013624 |  0.255930 |
|                 |             |        0.030146 |       0.062444 |     0.047519 |  0.140109 |
|                 |             |        0.062447 |       0.069764 |     0.025492 |  0.157702 |
|                 | Vidurkis:   |0.084803|0.070900|0.028878|0.184580|

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000           | list        |        0.036223 |       0.031262 |     0.011702 |  0.079186 |
|                 |             |        0.024652 |       0.031933 |     0.016031 |  0.072616 |
|                 |             |        0.029733 |       0.027574 |     0.015869 |  0.073176 |
|                 | Vidurkis:   |        0.030203 |       0.030256 |     0.014534 |  0.074993 |


| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 100000          | vector      |        0.186114 |       0.206523 |     0.111051 |  0.503689 |
|                 |             |        0.206727 |       0.222975 |     0.126360 |  0.556062 |
|                 |             |        0.183577 |       0.200969 |     0.126909 |  0.511455 |
|                 | Vidurkis:   |        0.192139 |        0.210156|      0.121440|  0.523735 |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 100000          | list        |        0.208268 |       0.204959 |     0.123139 |  0.536367 |
|                 |             |        0.184785 |       0.207737 |     0.110604 |  0.503127 |
|                 |             |        0.196075 |       0.205021 |     0.119220 |  0.520317 |
|                 | Vidurkis:   |         0.196376|       0.205906 |      0.117654|  0.519937 |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000000         | vector      |         1.66781 |        2.16399 |      1.26849 |   5.10029 |
|                 |             |         1.80656 |        2.21717 |      1.27366 |    5.2974 |
|                 |             |         1.86049 |        2.31014 |      1.27446 |   5.44508 |
|                 | Vidurkis:   |         1.77829 |        2.23043 |      1.27220 |   5.28092 |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000000         | list        |         1.76981 |        2.68693 |      1.66692 |   6.12366 |
|                 |             |         2.53398 |        3.32854 |      1.87165 |   7.73418 |
|                 |             |         2.58693 |        3.19908 |      1.77939 |   7.56539 |
|                 | Vidurkis:   |         2.29691 |        3.07152 |      1.77265 |   7.14108 |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000000        | vector      |         18.1777 |        24.5857 |      15.3738 |   58.1372 |
|                 |             |         21.4535 |        25.0047 |       16.348 |   62.8062 |
|                 |             |         24.3205 |        26.8906 |      17.1867 |   68.3978 |
|                 | Vidurkis:   |         21.3172 |        25.4937 |      16.3028 |   63.1137 |

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000000        | list        |         18.3375 |        26.6585 |      18.0124 |   63.0084 |
|                 |             |         25.7564 |        29.3404 |      17.1711 |   72.2679 |
|                 |             |         24.3806 |        28.5534 |      17.8623 |   70.7964 |
|                 | Vidurkis:   |          22.8248|         28.1841|       17.6819|   68.6909 |

------------TREČIOJI STRATEGIJA-------------

| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000            | vector      |       0.0015085 |       0.010105 |    0.0046282 | 0.0162417 |
|                 |             |       0.0239496 |      0.0060413 |    0.0021289 | 0.0321198 |
|                 |             |       0.0044234 |      0.0057682 |    0.0056001 | 0.0157917 |
|                 | Vidurkis:   |       0.0099605 |      0.0073048 |    0.0041191 | 0.0213844 |


| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000           | vector      |       0.0450395 |       0.026593 |    0.0163314 | 0.0879639 |
|                 |             |       0.0369897 |      0.0408678 |    0.0143769 | 0.0922344 |
|                 |             |       0.0368482 |      0.0242792 |    0.0156558 | 0.0767832 |
|                 | Vidurkis:   |       0.0396258 |      0.0305800 |    0.0154547 | 0.0856605 |


| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 100000          | vector      |         0.23283 |       0.262587 |     0.140169 |  0.635586 |
|                 |             |         0.25972 |       0.257926 |     0.141979 |  0.659624 |
|                 |             |        0.307319 |       0.270193 |     0.152027 |  0.729539 |
|                 | Vidurkis:   |        0.266623 |       0.263569 |     0.144725 |  0.674916 |



| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 1000000         | vector      |         2.19739 |        2.90994 |      1.43007 |   6.53739 |
|                 |             |         2.34142 |        3.07021 |      1.46777 |    6.8794 |
|                 |             |         2.53683 |        6.22064 |      1.42807 |   10.1855 |
|                 | Vidurkis:   |         2.35855 |        4.06693 |      1.44197 |   7.86743 |


| Įrašų  skaičius | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Iš viso:  |
|-----------------|-------------|-----------------|----------------|--------------|-----------|
| 10000000        | vector      |         24.0048 |        37.1952 |      13.8247 |   75.0247 |
|                 |             |          37.956 |        29.2248 |      13.9764 |   81.1572 |
|                 |             |         21.0603 |        33.3876 |      12.6792 |   67.1271 |
|                 | Vidurkis:   |         27.6737 |        33.2692 |      13.4934 |   74.4363 |


PROGRAMOS NAUDOJIMOSI INSTRUKCIJA:
Kompiliavimui ir paleidimui su CMake:
sukurkite katalogą kompiliavimui:
mkdir build
cd build

konfigūruokite projektą:
cmake ..

kompiliuokite:
cmake --build .

paleiskite programą:
su Unix/Linux/MacOS:
./studentai

su Windows:
studentai.exe



Programa susideda iš: Studentas.h, Studentas.cpp, StudentuGrupe.cpp ir main.cpp failų.
Paleidus programą pasirenkame kokią strategiją norime naudoti (trečioji veikia tik su vector).
Pasirinkus strategiją pasirenkame kokį konteinerį norime naudoti, tuomet kok5 veiksmą norime atlikti
<img width="942" height="299" alt="image" src="https://github.com/user-attachments/assets/26e427fc-eeb2-4cba-b3ad-a852a78a4443" />

Jei pasirenkame 1-3 variantus, toliau renkames pagal ką norime skirstyti studentus:
<img width="556" height="38" alt="image" src="https://github.com/user-attachments/assets/d4410a2b-c593-4403-afbd-5dcd1f939466" />

Tuomet pasirenkame, ar norime, jog jie būtų surūšiuoti pagal pavardę, ar ne.
Programai sekmingai suveikus matome, kokiuose failuose išsaugoti studentų duomenys.


Kode galima pasirinkti, ar naudojama std::vector ar std::list; readme faile matomi testavimo laiko rezultatai, kuriuose galima palyginti ar list, ar vector veikia greičiau (testavimai daryti su failais iš 1000, 10000, 100000, 1000000, 10000000 įrašų, po kelis kartus, yra pateiktas vidurkis).


--------------- v.03-------------
 Kode galima pasirinkti, ar naudojama std::vector ar std::list; readme faile matomi testavimo laiko rezultatai, kuriuose galima palyginti ar list, ar vector veikia greičiau (testavimai daryti su failais iš 1000, 10000, 100000, 1000000, 10000000 įrašų, po kelis kartus, yra pateiktas vidurkis).

-----------------v.02---------------------
studentai skirstomi į dvi grupes: kietiakai (balas >=5) ir vargšiukai (balas <5), suskirsčius į grupes programos naudotojas gali pasirinkti, ar nori, jog studentai būtų rūšiuojami pagal medianą ar vidurkį, ar pagal pavardę.

-----------------v0.1-------------------- 
Galima pasirinkti, ar norime studentus įvesti patys, ar sugeneruoti juos, ar nuskaityti iš failo. Taip pat galima pasirinkti, ar norime matyti vidurkį, ar medianą, ar abu. Dalis pirmųjų rezultatų išvedami komandinėje eilutėje, pagal vardus abėcėlės tvarka. Visi rezultatai pagal abėcėlę yra išvedami į atskirą failą "rezultatai.txt".
--------------v.pradinė -----------------

programoje duomenys nuskaitomi iš failo, o ne vedami ranka.


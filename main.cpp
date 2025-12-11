/**
 * @file main.cpp
 * @brief Programos įėjimo taškas ir Studentų demonstracijos
 *
 * Šiame faile vykdoma Studentas klasės ir StudentuGrupe funkcijų demonstracija.
 * Demonstracija apima abstrakčios klasės Zmogus naudojimą, studentų generavimą,
 * įvedimą iš failo, išvestį į failą, skirstymą pagal vidurkį/medianą,
 * bei pasirinkimą konteinerio tipo (vector arba list) ir strategijos.
 */
#include <iostream>
#include "StudentuGrupe.h"
#include <windows.h>
#include <sstream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;

/**
 * @brief Pagrindinė programos funkcija
 *
 * Funkcija vykdo Studentų demonstracijas pagal vartotojo pasirinkimus:
 * - Abstrakčios klasės demonstracija
 * - Studentų įvedimas ranka
 * - Atsitiktinių studentų generavimas
 * - Skaitymas iš failo
 * - Failo sugeneravimas su studentų duomenimis
 * - Studentų skirstymas pagal vidurkį arba medianą
 * - Pasirinkimas rikiuoti pagal pavardę
 *
 * @return int Grąžina 0 pavykus programos vykdymui
 */

int main() {


    // abstrakcios klases zmogus dmonstracija
    //Zmogus z; // nuimam koentara ir matom, kad nekompiliuoja
    // nes zmogus turi abstrakèià funkcija isvesti()
    // irodo, kad klase zmogus yra abstrakti

    Studentas demo("Jonas", "Jonaitis", {8, 9, 10}, 9);
    Zmogus* ptr = &demo;   /**< Naudojimas per abstrakčios klasės pointerį */
    cout << "Demonstracija per abstrakcios klases pointeri:\n";
    ptr->isvesti();         /**< Iškviečia Studentas::isvesti() per bazinę klasę */




    int strategija;
    cout << "Pasirinkite strategija (1 - du konteineriai, 2 - vienas su trynimais, 3 - partition (vector)): ";
    cin >> strategija;

    cout << "Pasirinkite konteineri:\n"
         << "1 - vector\n"
         << "2 - list\n> ";
    int konteineris;
    cin >> konteineris;

    StudentuGrupe grupe;
    grupe.naudotiVector = (konteineris == 1);

    cout << "Pasirinkite veiksma:\n"
         << "1 - Ivesti studentus\n"
         << "2 - Sugeneruoti atsitiktinius studentus\n"
         << "3 - Nuskaityti is failo\n"
         << "4 - Sugeneruoti faila su duomenimis\n> ";

    int pasirinkimas;
    cin >> pasirinkimas;

    if (pasirinkimas == 1) {
        /**< Rankinis studentų įvedimas */
        int kiek;
        cout << "Kiek studentu ivesti? ";
        cin >> kiek;
        for (int i = 0; i < kiek; ++i) {
            Studentas s;
            string vard, pav;
            cout << "Vardas: "; cin >> vard;
            cout << "Pavarde: "; cin >> pav;

            std::ostringstream oss;
            oss << vard << " " << pav << " ";

            cout << "Iveskite namu darbu pazymius (0 - baigti): ";
            int paz;
            while (cin >> paz && paz != 0) oss << paz << " ";

            cout << "Egzamino pazymys: ";
            int egz; cin >> egz;
            oss << egz;

std::istringstream iss(oss.str());
s.readStudent(iss);


            const Studentas* addr = grupe.prideti_studenta(s);
            cout << "Studento objektas saugomas konteineryje adrese: " << addr << endl;
        }
    }
    else if (pasirinkimas == 2) {
        /**< Atsitiktinių studentų generavimas */
        int kiek, nd_sk;
        cout << "Kiek studentu generuoti? "; cin >> kiek;
        cout << "Kiek ND pazymiu? "; cin >> nd_sk;
        grupe.generuoti_studentus(kiek, nd_sk);
    }
    else if (pasirinkimas == 3) {
        /**< Studentų nuskaitymas iš failo */
        string failas;
        cout << "Iveskite failo pavadinima: "; cin >> failas;
        grupe.skaityti_is_failo(failas);
    }
    else if (pasirinkimas == 4) {
        /**< Failo generavimas su studentų duomenimis */
        int kiek, nd_sk;
        string failas;
        cout << "Failo pavadinimas: "; cin >> failas;
        cout << "Studentu kiekis: "; cin >> kiek;
        cout << "ND kiekis: "; cin >> nd_sk;
        grupe.generuoti_faila(failas, kiek, nd_sk);
        return 0;
    }


    /**< Studentų skirstymas pagal vartotojo pasirinkimą */
    cout << "Skirstyti pagal (1 - vidurki, 2 - mediana): ";
    int pagal; cin >> pagal;

    cout << "Ar norite surikiuoti studentus pagal pavarde? (1 - ne, 2 - taip): ";
    int rikiuotiPagal;
    cin >> rikiuotiPagal;

    grupe.skirstyti_studentus(pagal, rikiuotiPagal, strategija);




    return 0;
}


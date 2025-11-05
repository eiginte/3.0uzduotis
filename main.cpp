#include <iostream>
#include "StudentuGrupe.h"
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {

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
        int kiek;
        cout << "Kiek studentu ivesti? ";
        cin >> kiek;
        for (int i = 0; i < kiek; ++i) {
            Studentas s;
            cout << "Vardas: "; cin >> s.vard;
            cout << "Pavarde: "; cin >> s.pav;

            cout << "Iveskite namu darbu pazymius (0 - baigti): ";
            int paz;
            while (cin >> paz && paz != 0) s.paz.push_back(paz);
            cout << "Egzamino pazymys: "; cin >> s.egzas;

            s.skaiciuoti_rezultatus();
            grupe.prideti_studenta(s);
        }
    }
    else if (pasirinkimas == 2) {
        int kiek, nd_sk;
        cout << "Kiek studentu generuoti? "; cin >> kiek;
        cout << "Kiek ND pazymiu? "; cin >> nd_sk;
        grupe.generuoti_studentus(kiek, nd_sk);
    }
    else if (pasirinkimas == 3) {
        string failas;
        cout << "Iveskite failo pavadinima: "; cin >> failas;
        grupe.skaityti_is_failo(failas);
    }
    else if (pasirinkimas == 4) {
        int kiek, nd_sk;
        string failas;
        cout << "Failo pavadinimas: "; cin >> failas;
        cout << "Studentu kiekis: "; cin >> kiek;
        cout << "ND kiekis: "; cin >> nd_sk;
        grupe.generuoti_faila(failas, kiek, nd_sk);
        return 0;
    }

    cout << "Skirstyti pagal (1 - vidurki, 2 - mediana): ";
    int pagal; cin >> pagal;

    cout << "Ar norite surikiuoti studentus pagal pavarde? (1 - ne, 2 - taip): ";
    int rikiuotiPagal;
    cin >> rikiuotiPagal;

    grupe.skirstyti_studentus(pagal, rikiuotiPagal);
}

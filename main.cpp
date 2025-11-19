#include "Studentas.h"
#include "StudentuGrupe.h"
#include <iostream>


using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
    int strategija;
    cout << "Pasirinkite strategija (1 - du konteineriai, 2 - vienas su trynimais, 3 - partition (vector)): ";
    cin >> strategija;

    cout << "Pasirinkite konteineri:\n1 - vector\n2 - list\n> ";
    int konteineris; cin >> konteineris;

    StudentuGrupe grupe;
    grupe.naudotiVector = (konteineris == 1);

    cout << "Pasirinkite veiksma:\n1 - Ivesti studentus\n2 - Sugeneruoti atsitiktinius studentus\n3 - Nuskaityti is failo\n4 - Sugeneruoti faila su duomenimis\n> ";
    int pasirinkimas; cin >> pasirinkimas;

    if (pasirinkimas == 1) {
        int kiek; cout << "Kiek studentu ivesti? "; cin >> kiek;
        for (int i = 0; i < kiek; ++i) {
            Studentas s; s.readStudent(cin);
            const Studentas* addr = grupe.prideti_studenta(s);
            cout << "Studento objektas saugomas konteineryje adrese: " << static_cast<const void*>(addr) << endl;
        }
    } else if (pasirinkimas == 2) {
        int kiek, nd_sk;
        cout << "Kiek studentu generuoti? "; cin >> kiek;
        cout << "Kiek ND pazymiu? "; cin >> nd_sk;
        grupe.generuoti_studentus(kiek, nd_sk);
    } else if (pasirinkimas == 3) {
        string failas; cout << "Iveskite failo pavadinima: "; cin >> failas;
        grupe.skaityti_is_failo(failas);
    } else if (pasirinkimas == 4) {
        int kiek, nd_sk; string failas;
        cout << "Failo pavadinimas: "; cin >> failas;
        cout << "Studentu kiekis: "; cin >> kiek;
        cout << "ND kiekis: "; cin >> nd_sk;
        grupe.generuoti_faila(failas, kiek, nd_sk);
        return 0;
    }

    int pagal; cout << "Skirstyti pagal (1 - vidurki, 2 - mediana): "; cin >> pagal;
    int rikiuotiPagal; cout << "Ar norite surikiuoti studentus pagal pavarde? (1 - ne, 2 - taip): "; cin >> rikiuotiPagal;

    grupe.skirstyti_studentus(pagal, rikiuotiPagal, strategija);
}



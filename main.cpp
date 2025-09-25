
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;
using std::setprecision;
using std::fixed;


struct Studentas {
    string vard;
    string pav;
    vector<int> paz;
    int egzas;
    double vid;
    double med;
};

Studentas ivesk();
double sk_med(vector<int> paz);


int main() {
    vector<Studentas> Grupe;
    for (int j = 0; j < 3; j++) {
        cout << "Iveskite " << j + 1 << " studenta:\n";
        Grupe.push_back(ivesk());
    }


    cout << "Ka norite isvesti?" << endl;
    cout << "1 - Vidurki" << endl;
    cout << "2 - Mediana" << endl;
    cout << "3 - Abu (vidurki ir mediana)" << endl;
    cout << "Pasirinkite:" << endl;
    int pasirinkimas;
    cin >> pasirinkimas;
   


    cout << left << setw(15) << "Vardas:" << " | " << setw(20) << "Pavarde" << " | "; 
    if (pasirinkimas == 1)
        cout << "Vidurkis: ";
    else if (pasirinkimas == 2)
        cout << "Mediana: ";
    else
        cout << "Vidurkis|Mediana";
    cout << endl;

    for (auto temp : Grupe) {

        cout << left << setw(15) << temp.vard << " | " << setw(20) << temp.pav << " | ";
        if (pasirinkimas == 1)
            cout << fixed << setprecision(2) << temp.vid;
        else if (pasirinkimas == 2)
            cout << fixed << setprecision(2) << temp.med;
        else
            cout << fixed << setprecision(2) << temp.vid << " | " << fixed << setprecision(2) << temp.med;
        
        cout << endl;
    }
}



Studentas ivesk()
{
    Studentas Laik;
    int sum = 0, n, m;
    cout << "Ivesk varda: ";
    cin >> Laik.vard;
    cout << "Ivesk pavarde: ";
    cin >> Laik.pav;

    cout << "Iveskite namu darbu pazymius (iveskite 0, jei norite baigti n.d. ivedima)"<< endl;
        while (true) {
            cin >> m;
            if (m == 0) break;
            Laik.paz.push_back(m);
            sum += m;
        }

    cout << "Iveskite egzamina: ";
    cin >> Laik.egzas;

    if (!Laik.paz.empty()) {
        Laik.vid = Laik.egzas * 0.6 + double(sum) / double(Laik.paz.size()) * 0.4;
        Laik.med = Laik.egzas * 0.6 + sk_med(Laik.paz) * 0.4;
    }
    else {
        Laik.vid = Laik.egzas * 0.6;
        Laik.med = Laik.egzas * 0.6;
    }

    return Laik;
}

double sk_med(vector<int> paz) {
    sort(paz.begin(), paz.end());
    size_t dydis = paz.size();

    if (dydis % 2 == 0)
        return (paz[dydis / 2 - 1] + paz[dydis / 2]) / 2.0;
    else
        return paz[dydis / 2];
}
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

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
using std::ifstream;
using std::istringstream;




struct Studentas {
    string vard;
    string pav;
    vector<int> paz;
    int egzas;
    double vid;
    double med;
};


double sk_med(vector<int> paz);

vector<Studentas> skaitymas(const string& filename) {
    vector<Studentas> Grupe;
    ifstream failas(filename);
    if (!failas) {
        cout << "Nepavyko atidaryti failo: " << filename << endl;
        return Grupe;
    }

    string header;
    getline(failas, header);

    string eilute;
    while (getline(failas, eilute)) {
        if (eilute.empty()) continue;

        istringstream iss(eilute);
        Studentas s;
        iss >> s.vard >> s.pav;

        vector<int> visiPaz;
        int sk;
        while (iss >> sk) {
            visiPaz.push_back(sk);
        }

        if (visiPaz.empty()) continue;

        s.egzas = visiPaz.back();
        visiPaz.pop_back();

        s.paz = visiPaz;

        if (!s.paz.empty()) {
            int sum = 0;
            for (int x : s.paz) sum += x;
            s.vid = s.egzas * 0.6 + (double)sum / s.paz.size() * 0.4;
            s.med = s.egzas * 0.6 + sk_med(s.paz) * 0.4;
        } else {
            s.vid = s.egzas * 0.6;
            s.med = s.egzas * 0.6;
        }

        Grupe.push_back(s);
    }

    return Grupe;
}

int main() {
    string failo_vardas = "randvardai.txt";
    vector<Studentas> Grupe = skaitymas(failo_vardas);

    if(Grupe.empty()){
        cout << "Tuscias failas arba klaida" << endl;
        return 1;
    }

    sort(Grupe.begin(),Grupe.end(), [](const Studentas& a, const Studentas&b){
         return a.vard<b.vard;
         });

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

    int kiek = 0;
    for (auto temp : Grupe) {

        cout << left << setw(15) << temp.vard << " | " << setw(20) << temp.pav << " | ";
        if (pasirinkimas == 1)
            cout << fixed << setprecision(2) << temp.vid;
        else if (pasirinkimas == 2)
            cout << fixed << setprecision(2) << temp.med;
        else
            cout << fixed << setprecision(2) << temp.vid << " | " << fixed << setprecision(2) << temp.med;


        cout << endl;
        if (++kiek == 20) break;
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

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <random>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::setprecision;
using std::fixed;
using std::ifstream;
using std::istringstream;
using std::ofstream;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::stringstream;


struct Studentas {
    string vard;
    string pav;
    vector<int> paz;
    int egzas{};
    double vid{};
    double med{};
    void skaiciuoti_rezultatus();

private:
    double skaiciuoti_mediana(vector<int> paz);
};


struct StudentuGrupe {
    vector<Studentas> visi;

    void prideti_studentą(const Studentas& s);
    void skaityti_is_failo(const string& failas);
    void generuoti_studentus(int kiek, int nd_sk);
    void generuoti_faila(const string& failas, int kiek, int nd_sk);
    void irasyti_i_faila(const vector<Studentas>& grupe, const string& failas);
    void skirstyti_studentus(int pagal_vid_ar_med);
};


void Studentas::skaiciuoti_rezultatus() {
    if (paz.empty()) {
        vid = egzas * 0.6;
        med = egzas * 0.6;
        return;
    }

    int suma = 0;
    for (int x : paz) suma += x;
    double vidurkis = static_cast<double>(suma) / paz.size();

    vid = egzas * 0.6 + vidurkis * 0.4;
    med = egzas * 0.6 + skaiciuoti_mediana(paz) * 0.4;
}

double Studentas::skaiciuoti_mediana(vector<int> paz) {
    std::sort(paz.begin(), paz.end());
    size_t n = paz.size();
    return (n % 2 == 0) ? (paz[n / 2 - 1] + paz[n / 2]) / 2.0 : paz[n / 2];
}

void StudentuGrupe::prideti_studentą(const Studentas& s) {
    visi.push_back(s);
}

void StudentuGrupe::skaityti_is_failo(const string& failas) {
    ifstream in(failas);
    if (!in) {
        cout << "Nepavyko atidaryti failo: " << failas << endl;
        return;
    }

    string header;
    getline(in, header);
    string eilute;

    while (getline(in, eilute)) {
        if (eilute.empty()) continue;
        istringstream iss(eilute);
        Studentas s;
        iss >> s.vard >> s.pav;

        vector<int> paz;
        int sk;
        while (iss >> sk) paz.push_back(sk);
        if (paz.empty()) continue;

        s.egzas = paz.back();
        paz.pop_back();
        s.paz = paz;
        s.skaiciuoti_rezultatus();
        visi.push_back(s);
    }
}

void StudentuGrupe::generuoti_studentus(int kiek, int nd_sk) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    for (int i = 1; i <= kiek; ++i) {
        Studentas s;
        s.vard = "Vardas" + std::to_string(i);
        s.pav = "Pavarde" + std::to_string(i);
        for (int j = 0; j < nd_sk; ++j) s.paz.push_back(dist(gen));
        s.egzas = dist(gen);
        s.skaiciuoti_rezultatus();
        visi.push_back(s);
    }
}

void StudentuGrupe::generuoti_faila(const string& failas, int kiek, int nd_sk) {
    ofstream out(failas);
    if (!out) {
        cout << "Nepavyko sukurti failo: " << failas << endl;
        return;
    }

    out << "Vardas Pavarde ";
    for (int i = 1; i <= nd_sk; ++i) out << "ND" << i << " ";
    out << "Egzaminas\n";

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    for (int i = 1; i <= kiek; ++i) {
        out << "Vardas" << i << " Pavarde" << i << " ";
        for (int j = 0; j < nd_sk; ++j) out << dist(gen) << " ";
        out << dist(gen) << "\n";
    }

    cout << "Failas \"" << failas << "\" sugeneruotas." << endl;
}

void StudentuGrupe::irasyti_i_faila(const vector<Studentas>& grupe, const string& failas) {
    ofstream out(failas);
    if (!out) {
        cout << "Nepavyko sukurti failo: " << failas << endl;
        return;
    }

    out << left << setw(15) << "Vardas" << " | " << setw(15) << "Pavarde"
        << " | " << setw(10) << "Vidurkis" << " | " << setw(10) << "Mediana\n";
    out << string(60, '-') << "\n";

    for (auto& s : grupe) {
        out << left << setw(15) << s.vard << " | "
            << setw(15) << s.pav << " | "
            << setw(10) << fixed << setprecision(2) << s.vid << " | "
            << setw(10) << fixed << setprecision(2) << s.med << "\n";
    }
}

void StudentuGrupe::skirstyti_studentus(int pagal_vid_ar_med) {
    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakiai;

    for (auto& s : visi) {
        double balas = (pagal_vid_ar_med == 1) ? s.vid : s.med;
        if (balas < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakiai.push_back(s);
    }

    irasyti_i_faila(vargsiukai, "vargsiukai.txt");
    irasyti_i_faila(kietiakiai, "kietiakiai.txt");

    cout << "Rezultatai issaugoti i failus: vargsiukai.txt ir kietiakiai.txt" << endl;
}

int main() {

    StudentuGrupe grupe;

    cout << "Pasirinkite veiksma:\n"
         << "1 - Ivesti studentus\n"
         << "2 - Sugeneruoti atsitiktinius studentus\n"
         << "3 - Nuskaityti is failo\n"
         << "4 - Sugeneruoti faila su duomenimis\n> ";

    int pasirinkimas;
    cin >> pasirinkimas;

    if (pasirinkimas == 1) {
        int kiek;
        cout << "Kiek studentų ivesti? ";
        cin >> kiek;

        for (int i = 0; i < kiek; ++i) {
            Studentas s;
            cout << "Vardas: ";
            cin >> s.vard;
            cout << "Pavarde: ";
            cin >> s.pav;

            cout << "Įveskite namu darbu pazymius (0 - baigti): ";
            int paz;
            while (cin >> paz && paz != 0) s.paz.push_back(paz);
            cout << "Egzamino pazymys: ";
            cin >> s.egzas;

            s.skaiciuoti_rezultatus();
            grupe.prideti_studentą(s);
        }
    }
    else if (pasirinkimas == 2) {
        int kiek, nd_sk;
        cout << "Kiek studentu generuoti? ";
        cin >> kiek;
        cout << "Kiek ND pazymių? ";
        cin >> nd_sk;
        grupe.generuoti_studentus(kiek, nd_sk);
    }
    else if (pasirinkimas == 3) {
        string failas;
        cout << "Iveskite failo pavadinima: ";
        cin >> failas;
        grupe.skaityti_is_failo(failas);
    }
    else if (pasirinkimas == 4) {
        int kiek, nd_sk;
        string failas;
        cout << "Failo pavadinimas: ";
        cin >> failas;
        cout << "Studentu kiekis: ";
        cin >> kiek;
        cout << "ND kiekis: ";
        cin >> nd_sk;
        grupe.generuoti_faila(failas, kiek, nd_sk);
        return 0;
    }

    cout << "Skirstyti pagal (1 - vidurki, 2 - mediana): ";
    int pagal;
    cin >> pagal;

    grupe.skirstyti_studentus(pagal);
}

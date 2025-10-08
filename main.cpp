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
using std::right;
using std::setprecision;
using std::fixed;
using std::ifstream;
using std::istringstream;
using std::ofstream;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::stringstream;
using std::sort;

struct Studentas {
    string vard;
    string pav;
    vector<int> paz;
    int egzas;
    double vid;
    double med;
};

double sk_med(vector<int> paz);
vector<Studentas> skaitymas(const string& filename);
Studentas ivesk();
void irasymas_i_faila(const vector<Studentas>& Grupe, const string& failo_vardas);
Studentas sugeneruoti_studento(int nd_sk);
void generuoti_faila_su_studentais(const string& failo_vardas, int kiek, int nd_sk);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    vector<Studentas> Grupe;

    cout << "Pasirinkite, kaip norite gauti studentu duomenis:" << endl;
    cout << "1 - Įvesti studentus patiems" << endl;
    cout << "2 - Sugeneruoti atsitiktinius balus" << endl;
    cout << "3 - Nuskaityti duomenis iš failo" << endl;
    cout << "4 - Sugeneruoti studentu faila (tik ND ir egzaminas)" << endl;
    cout << "Pasirinkite: ";

    int pradzios_pasirinkimas;
    cin >> pradzios_pasirinkimas;

    if (pradzios_pasirinkimas == 1) {
        char dar;
        do {
            Grupe.push_back(ivesk());
            cout << "Norite įvesti dar viena studentą? (t/n): ";
            cin >> dar;
        } while (dar == 't' || dar == 'T');
    }
    else if (pradzios_pasirinkimas == 2) {
        int kiek;
        cout << "Kiek studentu sugeneruoti? ";
        cin >> kiek;
        cout << "Kiek namu darbu generuoti kiekvienam studentui? ";
        int nd_sk;
        cin >> nd_sk;
        for (int i = 0; i < kiek; ++i)
            Grupe.push_back(sugeneruoti_studento(nd_sk));
    }
    else if (pradzios_pasirinkimas == 3) {
        string failo_vardas;
        cout << "Įveskite failo pavadinimą: ";
        cin >> failo_vardas;
        Grupe = skaitymas(failo_vardas);
        if (Grupe.empty()) {
            cout << "Tuscias failas arba klaida" << endl;
            return 1;
        }
    }
    else if (pradzios_pasirinkimas == 4) {
        int kiek, nd_sk;
        string failo_vardas;
        cout << "Kiek studentu sugeneruoti? ";
        cin >> kiek;
        cout << "Kiek namu darbu generuoti kiekvienam studentui? ";
        cin >> nd_sk;
        cout << "Įveskite failo pavadinimą (pvz. studentai.txt): ";
        cin >> failo_vardas;
        generuoti_faila_su_studentais(failo_vardas, kiek, nd_sk);
        cout << "Failas '" << failo_vardas << "' sugeneruotas." << endl;
        return 0;
    }
    else {
        cout << "Netinkamas pasirinkimas." << endl;
        return 1;
    }

    sort(Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b) {
        return a.vard < b.vard;
    });

    cout << "\nKa norite isvesti?" << endl;
    cout << "1 - Vidurki" << endl;
    cout << "2 - Mediana" << endl;
    cout << "3 - Abu (vidurki ir mediana)" << endl;
    cout << "Pasirinkite: ";

    int pasirinkimas;
    cin >> pasirinkimas;

    int skirstymas = pasirinkimas;
    if (pasirinkimas == 3) {
        cout << "Pagal ka norite skirstyti studentus? (1 - pagal vidurki, 2 - pagal mediana): ";
        cin >> skirstymas;
    }

    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakiai;

    for (auto& s : Grupe) {
        double balas = (skirstymas == 1) ? s.vid : s.med;
        if (balas < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakiai.push_back(s);
    }

    irasymas_i_faila(vargsiukai, "vargsiukai.txt");
    irasymas_i_faila(kietiakiai, "kietiakiai.txt");

    cout << "Rezultatai issaugoti i failus: vargsiukai.txt ir kietiakiai.txt" << endl;
}

void generuoti_faila_su_studentais(const string& failo_vardas, int kiek, int nd_sk) {
    ofstream out(failo_vardas);
    if (!out) {
        cout << "Nepavyko sukurti failo." << endl;
        return;
    }

    out << "Vardas Pavarde ";
    for (int i = 1; i <= nd_sk; ++i)
        out << "ND" << i << " ";
    out << "Egzaminas" << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    for (int i = 1; i <= kiek; ++i) {
        out << "Vardas" << i << " Pavarde" << i << " ";
        for (int j = 0; j < nd_sk; ++j)
            out << dist(gen) << " ";
        out << dist(gen) << endl;
    }
}

double sk_med(vector<int> paz) {
    std::sort(paz.begin(), paz.end());
    size_t dydis = paz.size();
    if (dydis % 2 == 0)
        return (paz[dydis / 2 - 1] + paz[dydis / 2]) / 2.0;
    else
        return paz[dydis / 2];
}

Studentas ivesk() {
    Studentas Laik;
    int sum = 0, m;
    cout << "Ivesk varda: ";
    cin >> Laik.vard;
    cout << "Ivesk pavarde: ";
    cin >> Laik.pav;

    cout << "Iveskite namu darbu pazymius (iveskite 0, jei norite baigti):" << endl;
    while (true) {
        cin >> m;
        if (m == 0) break;
        Laik.paz.push_back(m);
        sum += m;
    }

    cout << "Iveskite egzamino pazymi: ";
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

Studentas sugeneruoti_studento(int nd_sk) {
    static int nr = 1;
    Studentas Laik;

    stringstream ss;
    ss << nr;
    Laik.vard = "Vardas" + ss.str();
    Laik.pav = "Pavarde" + ss.str();
    ++nr;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> paz_dist(1, 10);
    uniform_int_distribution<> egz_dist(1, 10);

    for (int i = 0; i < nd_sk; ++i)
        Laik.paz.push_back(paz_dist(gen));

    Laik.egzas = egz_dist(gen);

    int sum = 0;
    for (auto x : Laik.paz) sum += x;
    Laik.vid = Laik.egzas * 0.6 + double(sum) / Laik.paz.size() * 0.4;
    Laik.med = Laik.egzas * 0.6 + sk_med(Laik.paz) * 0.4;

    return Laik;
}

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
        while (iss >> sk)
            visiPaz.push_back(sk);

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

void irasymas_i_faila(const vector<Studentas>& Grupe, const string& failo_vardas) {
    ofstream out(failo_vardas);
    if (!out) {
        cout << "Nepavyko sukurti failo: " << failo_vardas << endl;
        return;
    }

    out << left << setw(15) << "Vardas" << " | "
        << setw(20) << "Pavarde" << " | "
        << setw(10) << "Vidurkis" << " | "
        << setw(10) << "Mediana" << endl;
    out << string(60, '-') << endl;

    for (auto& s : Grupe) {
        out << left << setw(15) << s.vard << " | "
            << setw(20) << s.pav << " | "
            << setw(10) << fixed << setprecision(2) << s.vid << " | "
            << setw(10) << fixed << setprecision(2) << s.med << endl;
    }
}

#include "StudentuGrupe.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <algorithm>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::fixed;
using std::setprecision;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;



void StudentuGrupe::prideti_studenta(const Studentas& s) {
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
    if (!out) { cout << "Nepavyko sukurti failo: " << failas << endl; return; }

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
    if (!out) { cout << "Nepavyko sukurti failo: " << failas << endl; return; }

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

void StudentuGrupe::skirstyti_studentus(int pagal_vid_ar_med, int rikiuotiPagal) {
    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakiai;

    for (auto& s : visi) {
        double balas = (pagal_vid_ar_med == 1) ? s.vid : s.med;
        if (balas < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakiai.push_back(s);
    }

    if (pagal_vid_ar_med == 1) {
        std::sort(vargsiukai.begin(), vargsiukai.end(),
            [](const Studentas& a, const Studentas& b) { return a.vid > b.vid; });
        std::sort(kietiakiai.begin(), kietiakiai.end(),
            [](const Studentas& a, const Studentas& b) { return a.vid > b.vid; });
    } else {
        std::sort(vargsiukai.begin(), vargsiukai.end(),
            [](const Studentas& a, const Studentas& b) { return a.med > b.med; });
        std::sort(kietiakiai.begin(), kietiakiai.end(),
            [](const Studentas& a, const Studentas& b) { return a.med > b.med; });
    }

 if (rikiuotiPagal == 2) {
        std::sort(vargsiukai.begin(), vargsiukai.end(),
            [](const Studentas& a, const Studentas& b) { return a.pav < b.pav; });
        std::sort(kietiakiai.begin(), kietiakiai.end(),
            [](const Studentas& a, const Studentas& b) { return a.pav < b.pav; });
        cout << "Abu sarasai surikiuoti pagal pavarde." << endl;
    }

    irasyti_i_faila(vargsiukai, "vargsiukai.txt");
    irasyti_i_faila(kietiakiai, "kietiakiai.txt");

    cout << "Rezultatai issaugoti i failus: vargsiukai.txt ir kietiakiai.txt" << endl;
}

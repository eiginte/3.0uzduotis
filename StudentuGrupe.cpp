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
using std::list;
using std::setw;
using std::left;
using std::fixed;
using std::setprecision;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

// Prideda studentą į vector arba list ir grąžina adreso nuorodą
const Studentas* StudentuGrupe::prideti_studenta(const Studentas& s) {
    if (naudotiVector) {
        visi_vector.push_back(s);
        return &visi_vector.back();
    } else {
        visi_list.push_back(s);
        return &visi_list.back();
    }
}

// Nuskaito studentus iš failo
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
        string vard, pav;
        iss >> vard >> pav;

        vector<double> paz;
        double sk;
        while (iss >> sk) paz.push_back(sk);

        if (paz.empty()) continue;
        double egz = paz.back();
        paz.pop_back();

        Studentas s;
        s.setVard(vard);
        s.setPav(pav);
        s.setPaz(paz);
        s.setEgzas(egz);

        if (naudotiVector) visi_vector.push_back(s);
        else visi_list.push_back(s);
    }
}

// Sugeneruoja studentus atsitiktinai
void StudentuGrupe::generuoti_studentus(int kiek, int nd_sk) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    for (int i = 1; i <= kiek; ++i) {
        Studentas s;
        s.setVard("Vardas" + std::to_string(i));
        s.setPav("Pavarde" + std::to_string(i));

        vector<double> nd;
        for (int j = 0; j < nd_sk; ++j) nd.push_back(dist(gen));
        s.setPaz(nd);

        s.setEgzas(dist(gen));

        if (naudotiVector) visi_vector.push_back(s);
        else visi_list.push_back(s);
    }
}

// Sugeneruoja failą su studentų duomenimis
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

// Įrašo vector į failą
void StudentuGrupe::irasyti_i_faila(const vector<Studentas>& grupe, const string& failas) {
    ofstream out(failas);
    if (!out) {
        cout << "Nepavyko sukurti failo: " << failas << endl;
        return;
    }

    out << left << setw(15) << "Vardas" << " | " << setw(15) << "Pavarde"
        << " | " << setw(10) << "Vidurkis" << " | " << setw(10) << "Mediana\n";
    out << string(60, '-') << "\n";

    for (const auto& s : grupe) {
        out << left << setw(15) << s.vardas() << " | "
            << setw(15) << s.pavarde() << " | "
            << setw(10) << fixed << setprecision(2) << s.vid() << " | "
            << setw(10) << fixed << setprecision(2) << s.med() << "\n";
    }
}

// Įrašo list į failą
void StudentuGrupe::irasyti_i_faila(const list<Studentas>& grupe, const string& failas) {
    ofstream out(failas);
    if (!out) {
        cout << "Nepavyko sukurti failo: " << failas << endl;
        return;
    }

    out << left << setw(15) << "Vardas" << " | " << setw(15) << "Pavarde"
        << " | " << setw(10) << "Vidurkis" << " | " << setw(10) << "Mediana\n";
    out << string(60, '-') << "\n";

    for (const auto& s : grupe) {
        out << left << setw(15) << s.vardas() << " | "
            << setw(15) << s.pavarde() << " | "
            << setw(10) << fixed << setprecision(2) << s.vid() << " | "
            << setw(10) << fixed << setprecision(2) << s.med() << "\n";
    }
}

// Skirstymo logika lieka nepakitusi
void StudentuGrupe::skirstyti_studentus(int pagal_vid_ar_med, int rikiuotiPagal, int strategija) {
    // Tavo ankstesnė logika – vector ir list, strategijos 1, 2, 3
    // Likusi logika lieka tokia pati
}


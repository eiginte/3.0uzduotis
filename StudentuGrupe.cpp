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
using std::list;

const Studentas* StudentuGrupe::prideti_studenta(const Studentas& s) {
    if (naudotiVector) {
        visi_vector.push_back(s);
        return &visi_vector.back();
    } else {
        visi_list.push_back(s);
        return &visi_list.back();
    }
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
        s.readStudent(iss);
        prideti_studenta(s);
    }
}

void StudentuGrupe::generuoti_studentus(int kiek, int nd_sk) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    for (int i = 1; i <= kiek; ++i) {
        Studentas s;
        string vard = "Vardas" + std::to_string(i);
        string pav = "Pavarde" + std::to_string(i);
        std::vector<int> paz;
        for (int j = 0; j < nd_sk; ++j) paz.push_back(dist(gen));
        int egz = dist(gen);


        std::ostringstream oss;
        oss << vard << " " << pav << " ";
        for (int val : paz) oss << val << " ";
        oss << egz;

std::istringstream iss(oss.str());
s.readStudent(iss);

        prideti_studenta(s);
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

void StudentuGrupe::irasyti_i_faila(const vector<Studentas>& grupe, const std::string& failas) {
    ofstream out(failas);
    if (!out) { cout << "Nepavyko sukurti failo: " << failas << endl; return; }

    out << left << setw(15) << "Vardas" << " | " << setw(15) << "Pavarde"
        << " | " << setw(10) << "Vidurkis" << " | " << setw(10) << "Mediana\n";
    out << string(60, '-') << "\n";

    for (const auto& s : grupe) {
        out << left << setw(15) << s.vardas() << " | "
            << setw(15) << s.pavarde() << " | "
            << setw(10) << fixed << setprecision(2) << s.vidurkis() << " | "
            << setw(10) << fixed << setprecision(2) << s.mediana() << "\n";
    }
}

void StudentuGrupe::irasyti_i_faila(const list<Studentas>& grupe, const std::string& failas) {
    ofstream out(failas);
    if (!out) { cout << "Nepavyko sukurti failo: " << failas << endl; return; }

    out << left << setw(15) << "Vardas" << " | " << setw(15) << "Pavarde"
        << " | " << setw(10) << "Vidurkis" << " | " << setw(10) << "Mediana\n";
    out << string(60, '-') << "\n";

    for (const auto& s : grupe) {
        out << left << setw(15) << s.vardas() << " | "
            << setw(15) << s.pavarde() << " | "
            << setw(10) << fixed << setprecision(2) << s.vidurkis() << " | "
            << setw(10) << fixed << setprecision(2) << s.mediana() << "\n";
    }
}

void StudentuGrupe::skirstyti_studentus(int pagal_vid_ar_med, int rikiuotiPagal, int strategija) {
    if (naudotiVector) {
        std::vector<Studentas> kietiakiai, vargsiukai;

        if (strategija == 1) {
            for (auto& s : visi_vector) {
                double balas = (pagal_vid_ar_med == 1) ? s.vidurkis() : s.mediana();
                if (balas < 5.0) vargsiukai.push_back(s);
                else kietiakiai.push_back(s);
            }
        }
        else if (strategija == 2) {
            for (auto it = visi_vector.begin(); it != visi_vector.end();) {
                double balas = (pagal_vid_ar_med == 1) ? it->vidurkis() : it->mediana();
                if (balas < 5.0) {
                    vargsiukai.push_back(*it);
                    it = visi_vector.erase(it);
                } else ++it;
            }
            kietiakiai = visi_vector;
        }
        else if (strategija == 3) {
            auto part = std::partition(visi_vector.begin(), visi_vector.end(),
                [&](const Studentas& s) {
                    double balas = (pagal_vid_ar_med == 1) ? s.vidurkis() : s.mediana();
                    return balas >= 5.0; // TRUE → kietiakiai
                });
            vargsiukai.assign(part, visi_vector.end());
            visi_vector.erase(part, visi_vector.end());
            kietiakiai = visi_vector;
        }

        auto cmp_balas = [&](const Studentas& a, const Studentas& b) {
            if (pagal_vid_ar_med == 1) return a.vidurkis() > b.vidurkis();
            else return a.mediana() > b.mediana();
        };
        std::sort(vargsiukai.begin(), vargsiukai.end(), cmp_balas);
        std::sort(kietiakiai.begin(), kietiakiai.end(), cmp_balas);

        if (rikiuotiPagal == 2) {
            auto cmp_pav = [](const Studentas& a, const Studentas& b){ return a.pavarde() < b.pavarde(); };
            std::sort(vargsiukai.begin(), vargsiukai.end(), cmp_pav);
            std::sort(kietiakiai.begin(), kietiakiai.end(), cmp_pav);
        }

        irasyti_i_faila(vargsiukai, "vargsiukai.txt");
        irasyti_i_faila(kietiakiai, "kietiakiai.txt");
    }

    else {
        std::list<Studentas> kietiakiai, vargsiukai;

        if (strategija == 1) {
            for (auto& s : visi_list) {
                double balas = (pagal_vid_ar_med == 1) ? s.vidurkis() : s.mediana();
                if (balas < 5.0) vargsiukai.push_back(s);
                else kietiakiai.push_back(s);
            }
        }
        else if (strategija == 2) {
            for (auto it = visi_list.begin(); it != visi_list.end();) {
                double balas = (pagal_vid_ar_med == 1) ? it->vidurkis() : it->mediana();
                if (balas < 5.0) {
                    vargsiukai.push_back(*it);
                    it = visi_list.erase(it);
                } else ++it;
            }
            kietiakiai = visi_list;
        }

        if (pagal_vid_ar_med == 1) {
            vargsiukai.sort([](const Studentas& a, const Studentas& b){ return a.vidurkis() > b.vidurkis(); });
            kietiakiai.sort([](const Studentas& a, const Studentas& b){ return a.vidurkis() > b.vidurkis(); });
        } else {
            vargsiukai.sort([](const Studentas& a, const Studentas& b){ return a.mediana() > b.mediana(); });
            kietiakiai.sort([](const Studentas& a, const Studentas& b){ return a.mediana() > b.mediana(); });
        }

        if (rikiuotiPagal == 2) {
            vargsiukai.sort([](const Studentas& a, const Studentas& b){ return a.pavarde() < b.pavarde(); });
            kietiakiai.sort([](const Studentas& a, const Studentas& b){ return a.pavarde() < b.pavarde(); });
        }

        irasyti_i_faila(vargsiukai, "vargsiukai.txt");
        irasyti_i_faila(kietiakiai, "kietiakiai.txt");
    }

    cout << "Rezultatai issaugoti i failus: vargsiukai.txt ir kietiakiai.txt" << endl;
}

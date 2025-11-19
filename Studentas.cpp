#include "Studentas.h"
#include <algorithm>
#include <numeric>
#include <iostream>


void Studentas::skaiciuoti_rezultatus() {
    if (paz_.empty()) {
        vid_ = egzas_ * 0.6;
        med_ = egzas_ * 0.6;
        return;
    }

    int suma = std::accumulate(paz_.begin(), paz_.end(), 0);
    double vidurkis = static_cast<double>(suma) / paz_.size();

    vid_ = egzas_ * 0.6 + vidurkis * 0.4;
    med_ = egzas_ * 0.6 + skaiciuoti_mediana(paz_) * 0.4;
}


double Studentas::skaiciuoti_mediana(std::vector<int> paz) const {
    if (paz.empty()) return 0;
    std::sort(paz.begin(), paz.end());
    size_t n = paz.size();
    return (n % 2 == 0) ? (paz[n / 2 - 1] + paz[n / 2]) / 2.0 : paz[n / 2];
}


std::istream& Studentas::readStudent(std::istream& is) {
    is >> vardas_ >> pavarde_;
    int pazymys;
    paz_.clear();

    while (is >> pazymys) {
        paz_.push_back(pazymys);
        if (is.peek() == '\n') break;
    }

    is >> egzas_;
    skaiciuoti_rezultatus();

    return is;
}


double Studentas::galBalas(double (*funkcija)(std::vector<double>)) const {
    if (paz_.empty()) return egzas_;
    std::vector<double> nd(paz_.begin(), paz_.end());
    double ndRez = funkcija ? funkcija(nd) : 0;
    return 0.4 * ndRez + 0.6 * egzas_;
}


bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool comparePagalEgza(const Studentas& a, const Studentas& b) {
    return a.egzas() < b.egzas();
}

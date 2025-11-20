#include "Studentas.h"
#include <algorithm>
#include <numeric>
#include <iostream>

double Studentas::skaiciuoti_mediana(std::vector<int> paz) const {
    if (paz.empty()) return 0.0;

    std::sort(paz.begin(), paz.end());
    size_t n = paz.size();

    if (n % 2 == 0)
        return (paz[n/2 - 1] + paz[n/2]) / 2.0;
    else
        return paz[n/2];
}

double Studentas::galBalas(double (*funkcija)(std::vector<double>)) const {
    if (!funkcija) return 0.0;

    std::vector<double> temp;
    temp.reserve(paz_.size());
    for (int x : paz_) temp.push_back(x);

    return funkcija(temp);
}

void Studentas::skaiciuoti_rezultatus() {
    if (!paz_.empty()) {
        double suma = std::accumulate(paz_.begin(), paz_.end(), 0.0);
        vid_ = suma / paz_.size();
        med_ = skaiciuoti_mediana(paz_);
    }
    else {
        vid_ = 0.0;
        med_ = 0.0;
    }
}


std::istream& Studentas::readStudent(std::istream& is) {
    paz_.clear();

    is >> vardas_ >> pavarde_;

    int paz;
    // Skaitome visus ND iki tol, kol randame egzamino lauką
    while (is >> paz) {
        if (paz < 0 || paz > 10) break;   // egzamino vieta
        paz_.push_back(paz);
    }

    egzas_ = paz;  // paskutinis nuskaitytas yra egzamino balas

    skaiciuoti_rezultatus();
    return is;
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

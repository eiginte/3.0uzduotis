#include "Studentas.h"
#include <algorithm>
#include <iostream>

Studentas::Studentas(std::istream& is) { readStudent(is); }

void Studentas::skaiciuoti_rezultatus() {
    if (nd_.empty()) {
        vid_ = egzaminas_ * 0.6;
        med_ = egzaminas_ * 0.6;
        return;
    }
    double suma = 0.0;
    for (double x : nd_) suma += x;
    double ndVid = suma / nd_.size();
    vid_ = egzaminas_ * 0.6 + ndVid * 0.4;
    med_ = egzaminas_ * 0.6 + skaiciuotiMediana(nd_) * 0.4;
}

double Studentas::skaiciuotiMediana(std::vector<double> paz) const {
    if (paz.empty()) return 0.0;
    std::sort(paz.begin(), paz.end());
    size_t n = paz.size();
    return (n % 2 == 0) ? (paz[n / 2 - 1] + paz[n / 2]) / 2.0 : paz[n / 2];
}

double Studentas::galBalas(double (*skaiciuotiMedianaFunc)(std::vector<double>)) const {
    double ndVid = 0.0;
    if (!nd_.empty()) {
        double suma = 0.0;
        for (double x : nd_) suma += x;
        ndVid = suma / nd_.size();
    }
    double medianaRez = (skaiciuotiMedianaFunc) ? skaiciuotiMedianaFunc(nd_) : skaiciuotiMediana(nd_);
    return egzaminas_ * 0.6 + ndVid * 0.4;
}

std::istream& Studentas::readStudent(std::istream& is) {
    nd_.clear();
    std::cout << "Vardas: "; is >> vardas_;
    std::cout << "Pavarde: "; is >> pavarde_;
    std::cout << "Iveskite namu darbu pazymius (0 - baigti): ";
    double paz; while (is >> paz && paz != 0) nd_.push_back(paz);
    std::cout << "Egzamino pazymys: "; is >> egzaminas_;
    skaiciuoti_rezultatus();
    return is;
}

bool compare(const Studentas& a, const Studentas& b) { return a.vid() > b.vid(); }
bool comparePagalPavarde(const Studentas& a, const Studentas& b) { return a.pavarde() < b.pavarde(); }
bool comparePagalEgza(const Studentas& a, const Studentas& b) { return a.egzas() > b.egzas(); }


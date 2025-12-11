/**
 * @file Studentas.cpp
 * @brief Studentas klasės funkcijų įgyvendinimas
 *
 * Šiame faile įgyvendintos Studentas klasės funkcijos:
 * - rezultato apskaičiavimas (vidurkis, mediana)
 * - duomenų nuskaitymas iš srauto
 * - pagalbinės lyginimo funkcijos
 */
#include "Studentas.h"
#include <algorithm>
#include <numeric>
#include <iostream>


/**
 * @brief Pagalbinė funkcija medianai apskaičiuoti
 * @param paz Vektorius pažymių
 * @return double Apskaičiuota mediana
 */
double Studentas::skaiciuoti_mediana(std::vector<int> paz) const {
    if (paz.empty()) return 0.0;

    std::sort(paz.begin(), paz.end());
    size_t n = paz.size();

    if (n % 2 == 0)
        return (paz[n/2 - 1] + paz[n/2]) / 2.0;
    else
        return paz[n/2];
}

/**
 * @brief Pagalbinė funkcija galutiniam balui apskaičiuoti
 * @param funkcija Funkcija, naudojama pažymių apdorojimui
 * @return double Grąžina apskaičiuotą balą
 */
double Studentas::galBalas(double (*funkcija)(std::vector<double>)) const {
    if (!funkcija) return 0.0;

    std::vector<double> temp;
    temp.reserve(paz_.size());
    for (int x : paz_) temp.push_back(x);

    return funkcija(temp);
}

/**
 * @brief Apskaičiuoja studento rezultatus (vidurkį ir medianą)
 */
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


/**
 * @brief Nuskaito studento duomenis iš įvesties srauto
 * @param is Įvesties srautas
 * @return std::istream& Grąžina įvesties srautą
 *
 * Nuskaito vardą, pavardę, namų darbų pažymius ir egzamino pažymį.
 * Paskutinis nuskaitytas skaičius laikomas egzamino pažymiu.
 */
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


/**
 * @brief Lygina studentus pagal vardą
 * @param a Pirmas studentas
 * @param b Antras studentas
 * @return true jei a.vardas() < b.vardas(), kitaip false
 */
bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

/**
 * @brief Lygina studentus pagal pavardę
 * @param a Pirmas studentas
 * @param b Antras studentas
 * @return true jei a.pavarde() < b.pavarde(), kitaip false
 */
bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

/**
 * @brief Lygina studentus pagal egzamino pažymį
 * @param a Pirmas studentas
 * @param b Antras studentas
 * @return true jei a.egzas() < b.egzas(), kitaip false
 */
bool comparePagalEgza(const Studentas& a, const Studentas& b) {
    return a.egzas() < b.egzas();
}

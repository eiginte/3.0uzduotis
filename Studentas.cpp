#include "Studentas.h"
#include <algorithm>

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

double Studentas::skaiciuoti_mediana(std::vector<int> paz) {
    std::sort(paz.begin(), paz.end());
    size_t n = paz.size();
    return (n % 2 == 0) ? (paz[n / 2 - 1] + paz[n / 2]) / 2.0 : paz[n / 2];
}

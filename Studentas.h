#pragma once
#include <string>
#include <vector>
#include  <algorithm>

struct Studentas {
    std::string vard;
    std::string pav;
    std::vector<int> paz;
    int egzas{};
    double vid{};
    double med{};

    void skaiciuoti_rezultatus();

private:
    double skaiciuoti_mediana(std::vector<int> paz);
};

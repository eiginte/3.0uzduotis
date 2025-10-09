#pragma once
#include "Studentas.h"
#include <vector>
#include <string>

struct StudentuGrupe {
    std::vector<Studentas> visi;

    void prideti_studenta(const Studentas& s);
    void skaityti_is_failo(const std::string& failas);
    void generuoti_studentus(int kiek, int nd_sk);
    void generuoti_faila(const std::string& failas, int kiek, int nd_sk);
    void irasyti_i_faila(const std::vector<Studentas>& grupe, const std::string& failas);
    void skirstyti_studentus(int pagal_vid_ar_med);
};

#pragma once
#include "Studentas.h"
#include <vector>
#include <list>
#include <string>

struct StudentuGrupe {
    std::vector<Studentas> visi_vector;
    std::list<Studentas> visi_list;
    bool naudotiVector = true;

    const Studentas* prideti_studenta(const Studentas& s);

    void skaityti_is_failo(const std::string& failas);
    void generuoti_studentus(int kiek, int nd_sk);
    void generuoti_faila(const std::string& failas, int kiek, int nd_sk);

    void irasyti_i_faila(const std::vector<Studentas>& grupe, const std::string& failas);
    void irasyti_i_faila(const std::list<Studentas>& grupe, const std::string& failas);

    void skirstyti_studentus(int pagal_vid_ar_med, int rikiuotiPagal, int strategija);
};

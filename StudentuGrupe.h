/**
 * @file StudentuGrupe.cpp
 * @brief StudentuGrupe struktûros funkcijø ágyvendinimas
 *
 * Ðiame faile ágyvendintos StudentuGrupe struktûros funkcijos:
 * - studentø pridëjimas á grupæ
 * - skaitymas ið failo
 * - generavimas
 * - skirstymas pagal vidurká arba medianà
 * - áraðymas á failà
 */

#pragma once
#include "Studentas.h"
#include <vector>
#include<list>
#include <string>

/**
 * @struct StudentuGrupe
 * @brief Struktûra, skirta studentø grupei saugoti ir valdyti
 *
 * Laiko studentus arba `std::vector`, arba `std::list`, priklausomai nuo `naudotiVector` parametro.
 * Pateikia funkcijas studentø pridëjimui, skaitymui, generavimui ir skirstymui.
 */
struct StudentuGrupe {
    std::vector<Studentas> visi_vector;/**< Studentai saugomi vektoriuje */
    std::list<Studentas> visi_list;/**< Studentai saugomi sàraðe */

    bool naudotiVector = true;/**< Nustato, kuris konteineris naudojamas */

    /**
     * @brief Prideda studentà á grupæ
     * @param s Pridedamas Studentas objektas
     * @return const Studentas* Adresas konteineryje, kuriame saugomas studentas
     */
    const Studentas* prideti_studenta(const Studentas& s);

        /**
     * @brief Skaito studentus ið failo
     * @param failas Failo pavadinimas
     */
    void skaityti_is_failo(const std::string& failas);

        /**
     * @brief Generuoja atsitiktinius studentus
     * @param kiek Kiek studentø sugeneruoti
     * @param nd_sk Kiek namø darbø paþymiø generuoti kiekvienam studentui
     */
    void generuoti_studentus(int kiek, int nd_sk);

        /**
     * @brief Generuoja failà su atsitiktiniais studentais
     * @param failas Failo pavadinimas
     * @param kiek Kiek studentø sugeneruoti
     * @param nd_sk Kiek namø darbø paþymiø generuoti kiekvienam studentui
     */
    void generuoti_faila(const std::string& failas, int kiek, int nd_sk);

        /**
     * @brief Áraðo studentus á failà (vector)
     * @param grupe Vektorius studentø
     * @param failas Failo pavadinimas
     */
    void irasyti_i_faila(const std::vector<Studentas>& grupe, const std::string& failas);

        /**
     * @brief Áraðo studentus á failà (list)
     * @param grupe Sàraðas studentø
     * @param failas Failo pavadinimas
     */
    void irasyti_i_faila(const std::list<Studentas>& grupe, const std::string& failas);

        /**
     * @brief Skirsto studentus pagal galutiná vidurká arba medianà
     * @param pagal_vid_ar_med 1 - skirstyti pagal vidurká, 2 - pagal medianà
     * @param rikiuotiPagal 1 - ne, 2 - rikiuoti pagal pavardæ
     * @param strategija 1 - du konteineriai, 2 - vienas su trynimais, 3 - partition (vector)
     */
    void skirstyti_studentus(int pagal_vid_ar_med, int rikiuotiPagal, int strategija);
};

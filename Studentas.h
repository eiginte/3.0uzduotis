/**
 * @file Studentas.h
 * @brief Studentas klasės deklaracija.
 *
 * Šiame faile aprašyta Studentas klasė, paveldima iš Zmogus.
 * Studentas saugo namų darbų pažymius, egzamino pažymį, skaičiuoja vidurkį
 * ir medianą, įgyvendina abstrakčią Zmogus::isvesti() funkciją ir palaiko
 * Rule of Three.
 */
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Zmogus.h"

/**
 * @class Studentas
 * @brief Paveldima klasė iš Zmogus, skirta studentų duomenims saugoti ir apdoroti
 *
 * Studentas klasė saugo studento namų darbų pažymius, egzamino pažymį,
 * apskaičiuoja vidurkį ir medianą, palaiko Rule of Three (Copy constructor ir assignment)
 * bei įgyvendina abstrakčią Zmogus::isvesti() funkciją.
 */
class Studentas : public Zmogus {
private:
    std::vector<int> paz_; /**< Namų darbų pažymiai */
    int egzas_; /**< Egzamino pažymys */
    double vid_; /**< Vidurkio rezultatas */
    double med_; /**< Medianos rezultatas */

     /**
     * @brief Pagalbinė funkcija medianai apskaičiuoti
     * @param paz Vektorius pažymių
     * @return double Apskaičiuota mediana
     */
    double skaiciuoti_mediana(std::vector<int> paz) const;

    /**
     * @brief Pagalbinė funkcija galutiniam balui apskaičiuoti
     * @param funkcija Pointeris į funkciją, naudojamą pažymių apdorojimui
     * @return double Galutinis balas
     */
    double galBalas(double (*funkcija)(std::vector<double>) = nullptr) const;

public:
    // constructors

        /**
     * @brief Default konstruktorius
     */
    Studentas()
        : Zmogus(), paz_(), egzas_(0), vid_(0), med_(0)
    {
        std::cout << "[DEFAULT CTOR] Sukurtas tuscias studentas\n";
    }

        /**
     * @brief Parametrizuotas konstruktorius
     * @param vard Vardas
     * @param pav Pavardė
     * @param paz Vektorius namų darbų pažymių
     * @param egzas Egzamino pažymys
     */
    Studentas(const std::string& vard, const std::string& pav,
              const std::vector<int>& paz, int egzas)
        : Zmogus(vard, pav), paz_(paz), egzas_(egzas), vid_(0), med_(0)
    {
        skaiciuoti_rezultatus();
        std::cout << "[PARAMETRIZED CTOR] Sukurtas studentas " << vardas_ << "\n";
    }

    /**
     * @brief Konstruktorius iš įvesties srauto
     * @param is Įvesties srautas
     */
    Studentas(std::istream& is)
        : Zmogus(), paz_(), egzas_(0), vid_(0), med_(0)
    {
        std::cout << "[STREAM CTOR] Kuriamas studentas is srauto\n";
        readStudent(is);
    }

    //rule of 3

    /**
     * @brief Kopijavimo konstruktorius
     * @param other Kitas studentas, kurį kopijuojame
     */
    Studentas(const Studentas& other)
        : Zmogus(other),       // <- kopijuojam is zmogus
          paz_(other.paz_),
          egzas_(other.egzas_),
          vid_(other.vid_),
          med_(other.med_)
    {
        std::cout << "[COPY CTOR] Kopijuojamas studentas: "
                  << other.vardas_ << " " << other.pavarde_ << "\n";
    }

    /**
     * @brief Kopijavimo priskyrimo operatorius
     * @param other Kitas studentas, kurį priskiriame
     * @return Studentas& Nurodo į šį objektą
     */
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            std::cout << "[COPY ASSIGN] Priskiriamas studentas: "
                      << other.vardas_ << " " << other.pavarde_ << "\n";

            Zmogus::operator=(other);  // <- priskiriam

            paz_ = other.paz_;
            egzas_ = other.egzas_;
            vid_ = other.vid_;
            med_ = other.med_;
        }
        return *this;
    }

    /**
     * @brief Destruktorius
     */
    ~Studentas() {
        std::cout << "[DESTRUCTOR] Naikinamas studentas: "
                  << vardas_ << " " << pavarde_ << "\n";
    }


    // getteriai

    /**
     * @brief Gauti egzamino pažymį
     * @return int Egzamino pažymys
     */
    inline int egzas() const { return egzas_; }

    /**
     * @brief Gauti vidurkį
     * @return double Vidurkis
     */
    inline double vidurkis() const { return vid_; }

    /**
     * @brief Gauti medianą
     * @return double Mediana
     */
    inline double mediana() const { return med_; }

    /**
     * @brief Gauti namų darbų pažymius
     * @return std::vector<int> Vektorius pažymių
     */
    inline std::vector<int> pazymiai() const { return paz_; }

    // ABSTRACT FUNCTION IMPLEMENTATION

    /**
     * @brief Išvesties funkcija (įgyvendinta iš Zmogus)
     */
    void isvesti() const override {
        std::cout << vardas_ << " " << pavarde_
                  << " | Vid: " << vid_
                  << " | Med: " << med_ << "\n";
    }

    // rezultatų skaičiavimas

    /**
     * @brief Apskaičiuoja vidurkį ir medianą
     */
    void skaiciuoti_rezultatus();

    // skaitymas iš srauto


    /**
     * @brief Skaitymas iš įvesties srauto
     * @param is Įvesties srautas
     * @return std::istream& Grąžina įvesties srautą
     */
    std::istream& readStudent(std::istream& is);
};


//lyginimo fjos

/**
 * @brief Lyginimas pagal vidurkį
 */
bool compare(const Studentas&, const Studentas&);

/**
 * @brief Lyginimas pagal pavardę
 */
bool comparePagalPavarde(const Studentas&, const Studentas&);

/**
 * @brief Lyginimas pagal egzamino pažymį
 */
bool comparePagalEgza(const Studentas&, const Studentas&);

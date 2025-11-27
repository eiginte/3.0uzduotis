#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Zmogus.h"

class Studentas : public Zmogus {
private:
    std::vector<int> paz_;
    int egzas_;
    double vid_;
    double med_;

    // pagalbinė funkcija medianai
    double skaiciuoti_mediana(std::vector<int> paz) const;

    // galutinio balo skaičiavimo funkcija
    double galBalas(double (*funkcija)(std::vector<double>) = nullptr) const;

public:
    // constructors

    Studentas()
        : Zmogus(), paz_(), egzas_(0), vid_(0), med_(0)
    {
        std::cout << "[DEFAULT CTOR] Sukurtas tuscias studentas\n";
    }

    Studentas(const std::string& vard, const std::string& pav,
              const std::vector<int>& paz, int egzas)
        : Zmogus(vard, pav), paz_(paz), egzas_(egzas), vid_(0), med_(0)
    {
        skaiciuoti_rezultatus();
        std::cout << "[PARAMETRIZED CTOR] Sukurtas studentas " << vardas_ << "\n";
    }

    Studentas(std::istream& is)
        : Zmogus(), paz_(), egzas_(0), vid_(0), med_(0)
    {
        std::cout << "[STREAM CTOR] Kuriamas studentas is srauto\n";
        readStudent(is);
    }

    //rule of 3

    // COPY CONSTRUCTOR
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

    // COPY ASSIGNMENT
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

    // DESTRUCTOR
    ~Studentas() {
        std::cout << "[DESTRUCTOR] Naikinamas studentas: "
                  << vardas_ << " " << pavarde_ << "\n";
    }


    // getteriai
    inline int egzas() const { return egzas_; }
    inline double vidurkis() const { return vid_; }
    inline double mediana() const { return med_; }
    inline std::vector<int> pazymiai() const { return paz_; }

    // ABSTRACT FUNCTION IMPLEMENTATION
    void isvesti() const override {
        std::cout << vardas_ << " " << pavarde_
                  << " | Vid: " << vid_
                  << " | Med: " << med_ << "\n";
    }

    // rezultatų skaičiavimas
    void skaiciuoti_rezultatus();

    // skaitymas iš srauto
    std::istream& readStudent(std::istream& is);
};


//lyginimo fjos
bool compare(const Studentas&, const Studentas&);
bool comparePagalPavarde(const Studentas&, const Studentas&);
bool comparePagalEgza(const Studentas&, const Studentas&);


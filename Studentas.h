#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> paz_;
    int egzas_;
    double vid_;
    double med_;

    // pagalbinė funkcija medianai
    double skaiciuoti_mediana(std::vector<int> paz) const;

    // galutinio balo skaičiavimo funkcija
    double galBalas(double (*funkcija)(std::vector<double>) = nullptr) const;

public:

    Studentas()
        : vardas_(), pavarde_(), paz_(), egzas_(0), vid_(0), med_(0) {}

    Studentas(const std::string& vard, const std::string& pav,
              const std::vector<int>& paz, int egzas)
        : vardas_(vard), pavarde_(pav), paz_(paz), egzas_(egzas)
    {
        skaiciuoti_rezultatus();
    }

    Studentas(std::istream& is) {
        readStudent(is);
    }

    Studentas(const Studentas& other)
        : vardas_(other.vardas_),
          pavarde_(other.pavarde_),
          paz_(other.paz_),
          egzas_(other.egzas_),
          vid_(other.vid_),
          med_(other.med_) {}

    Studentas(Studentas&& other) noexcept
        : vardas_(std::move(other.vardas_)),
          pavarde_(std::move(other.pavarde_)),
          paz_(std::move(other.paz_)),
          egzas_(other.egzas_),
          vid_(other.vid_),
          med_(other.med_) {}

    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
            paz_ = other.paz_;
            egzas_ = other.egzas_;
            vid_ = other.vid_;
            med_ = other.med_;
        }
        return *this;
    }

    Studentas& operator=(Studentas&& other) noexcept {
        if (this != &other) {
            vardas_ = std::move(other.vardas_);
            pavarde_ = std::move(other.pavarde_);
            paz_ = std::move(other.paz_);
            egzas_ = other.egzas_;
            vid_ = other.vid_;
            med_ = other.med_;
        }
        return *this;
    }



    ~Studentas() = default; // std::string ir std::vector išvalo patys


    // GET'ERIAI
    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }
    inline int egzas() const { return egzas_; }
    inline double vidurkis() const { return vid_; }
    inline double mediana() const { return med_; }
    inline std::vector<int> pazymiai() const { return paz_; }

    // rezultatų skaičiavimas
    void skaiciuoti_rezultatus();

    // skaitymas iš srauto
    std::istream& readStudent(std::istream&);
};



bool compare(const Studentas&, const Studentas&);
bool comparePagalPavarde(const Studentas&, const Studentas&);
bool comparePagalEgza(const Studentas&, const Studentas&);

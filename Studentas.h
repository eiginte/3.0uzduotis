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
    double galBalas(double (*funkcija)(std::vector<double>) = nullptr) const;


    // pagalbinė funkcija medianai
    double skaiciuoti_mediana(std::vector<int> paz) const;

public:
    // konstruktoriai
    Studentas() : egzas_(0), vid_(0), med_(0) { }
    Studentas(std::istream& is) { readStudent(is); }

    // get'eriai
    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }
    inline int egzas() const { return egzas_; }
    inline double vidurkis() const { return vid_; }
    inline double mediana() const { return med_; }
    inline std::vector<int> pazymiai() const { return paz_; }

    // metodas rezultatams skaiciuoti
    void skaiciuoti_rezultatus();

    // set'eriai / read'is
    std::istream& readStudent(std::istream&);
};


bool compare(const Studentas&, const Studentas&);
bool comparePagalPavarde(const Studentas&, const Studentas&);
bool comparePagalEgza(const Studentas&, const Studentas&);

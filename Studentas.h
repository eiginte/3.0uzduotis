#pragma once
#include <iostream>
#include <string>
#include <vector>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    double egzaminas_{0};
    std::vector<double> nd_;
    double vid_{0};
    double med_{0};

    void skaiciuoti_rezultatus();
    double skaiciuotiMediana(std::vector<double> paz) const;

public:
    Studentas() = default;
    Studentas(std::istream& is);
    std::istream& readStudent(std::istream& is);

    std::string vardas() const { return vardas_; }
    std::string pavarde() const { return pavarde_; }
    double egzas() const { return egzaminas_; }
    std::vector<double> nd() const { return nd_; }
    double vid() const { return vid_; }
    double med() const { return med_; }

    void setVard(const std::string& v) { vardas_ = v; }
    void setPav(const std::string& p) { pavarde_ = p; }
    void setPaz(const std::vector<double>& nd) { nd_ = nd; skaiciuoti_rezultatus(); }
    void setEgzas(double e) { egzaminas_ = e; skaiciuoti_rezultatus(); }

    double galBalas(double (*skaiciuotiMedianaFunc)(std::vector<double>) = nullptr) const;
};

bool compare(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b);
bool comparePagalEgza(const Studentas& a, const Studentas& b);


#pragma once
#include <string>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    // rule of 3

    // custom destructor (virtual, privalomas paveldejimui)
    virtual ~Zmogus() {}

    // copy constructor
    Zmogus(const Zmogus& other)
        : vardas_(other.vardas_), pavarde_(other.pavarde_) {}

    // copy assignment
    Zmogus& operator=(const Zmogus& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
        }
        return *this;
    }

    //constructr
    Zmogus() = default;

    Zmogus(const std::string& vard, const std::string& pav)
        : vardas_(vard), pavarde_(pav) {}

    // getters
    std::string vardas() const { return vardas_; }
    std::string pavarde() const { return pavarde_; }

    //abstrakti
    virtual void isvesti() const = 0;
};


/**
 * @file Zmogus.h
 * @brief Abstrakti bazinė klasė žmogui.
 *
 * Šiame faile aprašyta abstrakti Zmogus klasė, sauganti vardą ir pavardę,
 * bei apibrėžianti abstraktų metodą isvesti(), skirtą paveldėjimui kitose klasėse
 * (pvz., Studentas).
 */

#pragma once
#include <string>

/**
 * @class Zmogus
 * @brief Abstrakti bazinė klasė žmogui
 *
 * Klasė Zmogus saugo vardą ir pavardę bei apibrėžia abstraktų metodą isvesti().
 * Skirta paveldėjimui kitose klasėse (pvz., Studentas).
 */
class Zmogus {
protected:
    std::string vardas_; /**< Vardas */
    std::string pavarde_; /**< Pavardė */

public:

    //constructr

    /**
     * @brief Default konstruktorius
     */
    Zmogus() = default;

    /**
     * @brief Parametrizuotas konstruktorius
     * @param vard Vardas
     * @param pav Pavardė
     */
    Zmogus(const std::string& vard, const std::string& pav)
        : vardas_(vard), pavarde_(pav) {}

    // copy constructor

    /**
     * @brief Kopijavimo konstruktorius
     * @param other Kitas Zmogus objektas
     */
    Zmogus(const Zmogus& other)
        : vardas_(other.vardas_), pavarde_(other.pavarde_) {}


    /**
     * @brief Kopijavimo priskyrimo operatorius
     * @param other Kitas Zmogus objektas
     * @return Zmogus& Nurodo į šį objektą
     */
    Zmogus& operator=(const Zmogus& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
        }
        return *this;
    }

    /**
     * @brief Virtualus destruktorius, būtinas paveldėjimui
     */
    virtual ~Zmogus() {}


    // getters
    /**
     * @brief Gauti vardą
     * @return std::string Vardas
     */
    std::string vardas() const { return vardas_; }

    /**
     * @brief Gauti pavardę
     * @return std::string Pavardė
     */
    std::string pavarde() const { return pavarde_; }

    //abstrakti

    /**
     * @brief Abstraktus metodas išvesti informaciją apie žmogų
     *
     * Privalomas implementuoti paveldėtose klasėse.
     */
    virtual void isvesti() const = 0;
};

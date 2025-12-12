#include <gtest/gtest.h>
#include "Studentas.h"
#include "StudentuGrupe.h"
#include <vector>
#include <algorithm>



// Testas studenti pridejimui i grupe
TEST(StudentuGrupeTests, PridedaStudenta) {
    StudentuGrupe g;
    g.naudotiVector = true;

    std::vector<int> nd = {9, 7};
    Studentas s("Ona", "Onute", nd, 8);

    g.prideti_studenta(s);
    ASSERT_EQ(g.visi_vector.size(), 1);
    ASSERT_EQ(g.visi_vector[0].vardas(), "Ona");
    ASSERT_EQ(g.visi_vector[0].pavarde(), "Onute");
}

// Testas rikiavimo pagal pavarde
TEST(StudentasTests, RikiuojaPagalPavarde) {
    std::vector<Studentas> v = {
        Studentas("Jonas", "Bbb", {}, 0),
        Studentas("Petras", "Aaa", {}, 0)
    };

    std::sort(v.begin(), v.end(), [](const Studentas& a, const Studentas& b){
        return a.pavarde() < b.pavarde();
    });

    ASSERT_EQ(v[0].pavarde(), "Aaa");
    ASSERT_EQ(v[1].pavarde(), "Bbb");
}

// Testas rikiavimo pagal varda
TEST(StudentasTests, RikiuojaPagalVarda) {
    std::vector<Studentas> v = {
        Studentas("Jonas", "Bbb", {}, 0),
        Studentas("Petras", "Aaa", {}, 0)
    };

    std::sort(v.begin(), v.end(), [](const Studentas& a, const Studentas& b){
        return a.vardas() < b.vardas();
    });

    ASSERT_EQ(v[0].vardas(), "Jonas");
    ASSERT_EQ(v[1].vardas(), "Petras");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // Nukreipiame cout i "niekur", kad nesimatytu konstruktor/destruktoriu logu
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(nullptr);

    int result = RUN_ALL_TESTS();
    std::cout.rdbuf(oldCout);

    return result;
}



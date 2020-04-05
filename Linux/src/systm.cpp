// systm.cpp 

#include "systm.hpp"

// Pour faire une pause sous Linux
void pause() {
    std::cout << std::endl;
    std::cout << "Press enter to continue ...";
    std::cin.get(); 
}

// Pour afficher une chaine de caractères accentués sous Linux
void aout(const std::string& s) {
    std::cout << s;
}

// systm.cpp 

#include "systm.hpp"

// Pour faire une pause sous Windows
void pause() {
    std::cout << std::endl;
    system("pause");    
}

// Pour afficher une chaine de caractères accentués sous Windows
void aout(const std::string& s) {  
    char* c = new char[s.size()+1];
    CharToOemA(s.c_str(), c);
    std::cout << c;
    delete[] c;
}


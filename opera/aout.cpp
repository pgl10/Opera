// aout.cpp 

#include <iostream>
#include <windows.h>

void aout(std::string s) {  // pour afficher un chaine de caract�res accentu�s 
    char* c = new char[s.size()+1];
    CharToOemA(s.c_str(), c);
    std::cout << c;
    delete[] c;
}

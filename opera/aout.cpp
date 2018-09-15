// aout.cpp

#include <iostream>
#include <windows.h>

void aout(char* s) {  // pour afficher un chaine de caractères accentués 
    char* c = new char[strlen(s)+1];
    CharToOemA(s, c);
    std::cout << c;
    delete[] c;
} 

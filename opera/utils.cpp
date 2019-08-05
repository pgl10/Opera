// utils.cpp

#include "utils.hpp"

// Pour supprimer les ' ' dans cette instruction
void outspaces(std::string& line) {
    char lign1[1024];
    strcpy(lign1, line.c_str());
    char lign2[1024];
    int j = 0;
    for(unsigned int i=0; i<strlen(lign1); i++) 
        if(lign1[i] != ' ') {
            lign2[j] = lign1[i];
            ++j;
        }
    lign2[j] = '\0';
    line = std::string(lign2);
}

// Ce nom est-il valide ?
bool isname(const char* nom) {
    char alfa[64] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789";
    bool good = false;
    for(unsigned int i=0; i<52; i++) if(nom[0] == alfa[i]) {
        good = true;
        break;
    }
    if(!good) return false;
    for(unsigned int k=0; k<strlen(nom); k++) {
        good = false;
        for(unsigned int i=0; i<64; i++) if(nom[k] == alfa[i]) {
            good = true;
            break;
        }
        if(!good) return false;
    }
    return true;
}

// Ce nombre entier est-il valide ?
bool isnumb(const char* nbr) {
    if(strlen(nbr) == 0) return false;
    char alfa[11] = "0123456789";
    bool good = false;
    for(unsigned int k=0; k<strlen(nbr); k++) {
        good = false;
        for(unsigned int i=0; i<10; i++) if(nbr[k] == alfa[i]) {
            good = true;
            break;
        }
        if(!good) return false;
    }
    return true;
}

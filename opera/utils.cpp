// utils.cpp

#include "utils.hpp"

// Pour supprimer les ' ' au début de cette instruction
void espaces(std::string& line) {
    unsigned int i=0;
    while(i < line.size() && line[i] == ' ') ++i;
    line = line.substr(i);
}

// Pour supprimer les ' ' dans cette instruction
void outspaces(std::string& line) {
    unsigned int j = 0;
    char* chrs = new char[1+line.size()];
    for(unsigned int i=0; i<line.size(); i++) 
        if(line[i] != ' ') chrs[j++] = line[i];
    chrs[j++] = '\0';
    line = std::string(chrs);
    delete [] chrs;
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
        for(unsigned int i=0; i<63; i++) if(nom[k] == alfa[i]) {
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

// Ce nombre décimal est-il valide ?
// Un '.' et un seul est obligatoire 
// mais ni au début ni à la fin.
bool isdecim(const char* nbr) {
    if(strlen(nbr) == 0) return false;
    char alfa[11] = "0123456789";
    int np = -1;
    bool good = false;
    for(unsigned int k=0; k<strlen(nbr); k++) {
        good = false;
        for(unsigned int i=0; i<10; i++) if(nbr[k] == alfa[i]) {
            good = true;
            break;
        }
        if(!good) 
            if(nbr[k] == '.' && np == -1) {
                good = true;
                np = k;
            }
        if(!good) return false;
    }
    if(np<=0 || np==strlen(nbr)-1) return false;
    return true;
}

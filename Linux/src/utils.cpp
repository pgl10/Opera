// utils.cpp

#include "utils.hpp"

// Pour supprimer un éventuel commentaire en fin de ligne
void delcom(std::string& ligne) {
    std::size_t found = ligne.find("#");
    if(found != std::string::npos) ligne = ligne.substr(0, found);
}

// Pour supprimer tous les ' ' dans cette instruction
void outspaces(std::string& line) {
    unsigned int j = 0;
    char* chrs = new char[1+line.size()];
    for(unsigned int i=0; i<line.size(); i++) 
        if(line[i] != ' ') chrs[j++] = line[i];
    chrs[j++] = '\0';
    line = std::string(chrs);
    delete [] chrs;
}

// Pour supprimer les ' ' au début de cette instruction
void firstspaces(std::string& line) {
    unsigned int i=0;
    while(i < line.size() && line[i] == ' ') ++i;
    line = line.substr(i);
}

// Pour supprimer les ' ' au début de cette instruction
// et conserver les caractères avant le ' ' suivant.
void premiermot(std::string& line) {
    unsigned int i=0;
    while(i < line.size() && line[i] == ' ') ++i;
    line = line.substr(i);
    i = 0;
    while(i < line.size() && line[i] != ' ') ++i;
    line = line.substr(0, i);
}

// Pour valider un nom de variable sans aucun indice
bool isname0(const std::string& nom) {
    char alfa[64] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789";
    bool good = false;
    for(unsigned int i=0; i<52; i++) if(nom[0] == alfa[i]) {
        good = true;
        break;
    }
    if(!good) return false;
    for(unsigned int k=0; k<nom.size(); k++) {
        good = false;
        for(unsigned int i=0; i<63; i++) if(nom[k] == alfa[i]) {
            good = true;
            break;
        }
        if(!good) return false;
    }
    return true;
}

// Pour valider un nom de variable ayant éventuellement plusieurs indices
bool isname(const std::string& nom) {
    char alfa[66] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789[]";
    bool good = false;
    for(unsigned int i=0; i<52; i++) if(nom[0] == alfa[i]) {
        good = true;
        break;
    }
    if(!good) return false;
    for(unsigned int k=0; k<nom.size(); k++) {
        good = false;
        for(unsigned int i=0; i<65; i++) if(nom[k] == alfa[i]) {
            good = true;
            break;
        }
        if(!good) return false;
    }
    std::size_t found = nom.find_last_of("]");
    if(found != std::string::npos) if(nom.substr(found+1).size() != 0) return false;
    return true;
}

// Pour valider un nombre entier positif ou nul 
bool isnumb(const std::string& nbr) {
    if(nbr.size() == 0) return false;
    char alfa[11] = "0123456789";
    bool good = false;
    for(unsigned int k=0; k<nbr.size(); k++) {
        good = false;
        for(unsigned int i=0; i<10; i++) if(nbr[k] == alfa[i]) {
            good = true;
            break;
        }
        if(!good) return false;
    }
    return true;
}

// Pour valider un nombre décimal positif ou nul
// Un '.' et un seul est obligatoire 
// mais ni au début ni à la fin.
bool isdecim(const std::string& nbr) {
    if(nbr.size() == 0) return false;
    char alfa[11] = "0123456789";
    int np = -1;
    bool good = false;
    for(unsigned int k=0; k<nbr.size(); k++) {
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
    if(np<=0 || np==(int)nbr.size()-1) return false;
    return true;
}

// Pour valider une instruction comportant uniquement un mot-clé
bool instr(std::string& cmde, std::string& ligne, std::string keyw) {
    if(ligne == keyw) 
        if(cmde.find(keyw) != std::string::npos) return true;
    return false;
}

// Pour valider seulement le mot-clé de l'instruction ayant une suite
bool keywd(std::string& line, std::string& ligne, std::string keyw) {
    std::size_t n = keyw.size();
    if(!(line.size() == n && ligne.size() > n)) return false;
    if(!(ligne.substr(0, n).compare(keyw) == 0)) return false;
    return true;
}

// Pour obtenir le niveau actuel de la précision utilisable
// pour une approximation d'une racine n-ième irrationnelle
// faire : k = approxim(0);  (par défaut : k = 64)
// Si n > 0 on archive un nouveau niveau actuel utilisable.
int approxim(int n) {
    static int k = 64;
    if(n > 0) {
        k = n;
        return k;
    }
    else return k;
} 

// Pour mettre à jour le niveau de la précison utilisable
// pour une approximation d'une racine n-ième irrationnelle
void setapprox(std::string ligne){	
    if(isnumb(ligne)) {
        char alfa[11] = "0123456789";
        int n = 0;
        for(unsigned int k=0; k<ligne.size(); k++)
            n = n*10 + (ligne[k]-alfa[0]);
        if(n < 4) {
            std::cout << "il faut un entier plus grand que 3" << std::endl;
            return;
        }
        int u = approxim(n);
        std::cout << u << std::endl;
        return;
    }
    bigRa x;
    chercherra(lect, ligne, x);
    // Si le nombre x n'est pas trouvé on a ici : x = 0/1
    Integer xn=x.getNum(), xd=x.getDen();
    if(xd != 1 || xn <= 0) {
        std::cout << "il faut un entier positif" << std::endl;
        return;
    }
    if(xn < 4) {
        std::cout << "il faut un entier plus grand que 3" << std::endl;
        return;
    }
    int v = approxim((int)xn);
    std::cout << v << std::endl;
} 

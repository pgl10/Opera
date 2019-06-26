// eval.cpp

#include "eval.hpp"

// Pour obtenir la valeur d'une variable dans listera
bool vval(std::string& name, bigRa& r) {
    bigRa z;
    r = z;
    char* nom = new char[1+name.size()];
    strcpy(nom, name.c_str());
    elemra* elra = chercherra(nom);
    if(elra == NULL) return false;
    bigRa* pra = elra->ra;  
    r = *pra;
    return true;                  
}

// Pour calculer la valeur d'une instruction définie
bool eval(std::string ligne, bigRa& r) {
    int s = 1;
    if(ligne[0] == '-') {
        s = -1;
        ligne = ligne.substr(1);
    }
    if(vval(ligne, r)) {
        if(s < 0) r.setNum(-r.getNum());
        return true;
    }
    // r = 0 si l'instruction n'est pas reconnue
    bigRa z;
    r = z;
    char* line = new char[1+ligne.size()];
    strcpy(line, ligne.c_str());
    if(isnumb(line)) {
        r = bigRa(line);
        if(s < 0) r.setNum(-r.getNum());
        delete [] line;
        return true;
    }
    delete [] line;
    // nbop : nombre d'opérateurs présents
    int nbop = 0;
    std::size_t found, pos, pm;
    found = ligne.find("+");
    if(found != std::string::npos) {++nbop; pos=found;}
    found = ligne.find("*");
    if(found != std::string::npos) {++nbop; pos=found;}
    found = ligne.find("/");
    if(found != std::string::npos) {++nbop; pos=found;}
    found = ligne.find("^");
    if(found != std::string::npos) {++nbop; pos=found;}
    found = ligne.find("-");
    if(found != std::string::npos) {
        pm=found;
        bool bon = true;
        if(pm > 0 && ligne[pm-1] == '+') bon = false;
        if(pm > 0 && ligne[pm-1] == '*') bon = false;
        if(pm > 0 && ligne[pm-1] == '/') bon = false;
        if(pm > 0 && ligne[pm-1] == '^') bon = false;
        // bon = true pour l'opérateur - à 2 arguments
        if(bon) {
            ++nbop;
            pos = pm;
        }
    }
    // il faut un seul opérateur : ni au début, ni à la fin
    if(nbop != 1) return false;
    if(pos==(ligne.size()-1) || pos==0) return false;
    std::string left = ligne.substr(0, pos);
    std::string right = ligne.substr(pos+1);
    // r1 et r2 seront les deux opérandes
    bigRa r1, r2;
    Integer nleft, nright;
    if(isnumb(left.c_str())) {
        nleft = left.c_str();
        r1.setNum(nleft);
        r1.setDen(1);
    }
    else if(!vval(left, r1)) return false;
    if(s < 0) r1.setNum(-r1.getNum());
    int s2 = 1;
    if(right[0] == '-') {
        s2 = -1;
        right = right.substr(1);
    }
    bool good = false;
    if(isnumb(right.c_str())) {
        nright = right.c_str();
        r2.setNum(nright);
        r2.setDen(1);
        good = true;
    }
    else if(vval(right, r2)) good = true;
    if(s2<0) r2.setNum(-r2.getNum());
    if(!good) return false;
    // calcul final du résultat
    if(ligne[pos] == '+') r=r1.additionner(r2);
    if(ligne[pos] == '-') r=r1.soustraire(r2);
    if(ligne[pos] == '*') r=r1.multiplier(r2);
    if(ligne[pos] == '^') {
        if(r2.getDen() != 1) {
            aout("l'exposant doit être un entier.\n");
            return false;
		}
        int n2 = r2.getNum();
        r=r1.puissance(n2);
    }
    if(ligne[pos] == '/') r=r1.diviser(r2);
    r.simplifier();
    return true;
}

// Pour convertir en nombre réel le résultat obtenu
bool rval(std::string& name, double& r) {
    r = 0.0;
    bigRa x;
    bool good = eval(name, x);
    if(!good) return false;
    r = double(x.getNum())/double(x.getDen());
    return true;                  
}

// Pour calculer la partie entière d'une variable
// ou d'une expression arithmétique.
bool nval(std::string& name, Integer& r) {
    bigRa x;
    bool good = eval(name, x);
    if(!good) return false;
    r = entier(x);
    return true;                  
}


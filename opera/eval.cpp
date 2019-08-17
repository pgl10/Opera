// eval.cpp

#include "eval.hpp"

// Pour obtenir la valeur d'une variable dans listera
bool vval(std::string& name, bigRa& r) {
    bigRa z;
    r = z;
    char* nom = new char[1+name.size()];
    strcpy(nom, name.c_str());
    elemra* elra = chercherra(nom);
    delete [] nom;
    if(elra == NULL) return false;
    bigRa* pra = elra->ra;  
    r = *pra;
    return true;                  
}

bigRa decimal(std::string str) {
    std::size_t found;
    found = str.find('.');
    std::string sn, sm;
    sn = str.substr(0, found);
    sm = str.substr(found+1);
    Integer n=0, m=0;
    if(sn.size()>0) n = sn.c_str();
    if(sm.size()>0) m = sm.c_str();
    bigRa d = bigRa(10)^sm.size();
    bigRa r = bigRa(n) + bigRa(m)/d;
    return r;
}

// Pour obtenir la valeur d'un entier ou 
// d'un nombre décimal ou d'une variable
bool cval(std::string str, bigRa& r) {
    int s = 1;
    if(str.size() > 0 && str[0] == '-') {
        s = -1;
        str = str.substr(1);
    }
    if(isnumb(str.c_str())) {
        Integer n;
        n = str.c_str();
        r = bigRa(n);
        if(s < 0) r.setNum(-r.getNum());
        return true;
    }
    if(isdecim(str.c_str())) {
        r = decimal(str);
        if(s < 0) r.setNum(-r.getNum());
        return true;
    }
    if(vval(str, r)) {
        if(s < 0) r.setNum(-r.getNum());
        return true;
    }
    return false;    
}

// Pour calculer le contenu des parenthèses
bool parentheses(std::string& ligne) {
    std::string ops = "^/*-+<>";
    bool pars;
    do {
        pars = false;
        std::size_t found = ligne.find('(');
        // S'il y a encore des parenthèses dans ligne
        if(found != std::string::npos) {
            pars = true;
            std::string front, back;
            if(found == 0) front = "";
            else {
                front = ligne.substr(0, found);
                if(ops.find(front[front.size()-1]) == std::string::npos) return false;
            }
            std::size_t last = std::string::npos;
            int niv = 0;
            unsigned int suiv = found + 1;
            while(suiv < ligne.size()) {
                if(ligne[suiv] == ')' && niv == 0) {
                    last = suiv;
                    break;
                }
                if(ligne[suiv] == '(') niv = niv + 1;
                if(ligne[suiv] == ')') niv = niv - 1;
                suiv = suiv + 1;
            }
            if(last == std::string::npos) return false;
            // ligne[found] = '(' correspond à ligne[last] = ')'
            if(last == ligne.size()-1) back = "";
            else {
                back = ligne.substr(last+1);
                if(ops.find(back[0]) == std::string::npos) return false;
            }
            std::string subligne = ligne.substr(found+1, last-found-1);
            // S'il faut effectuer le même traitement à subligne 
            if(subligne.find('(') != std::string::npos) parentheses(subligne);
            bigRa subval;
            if(eval(subligne, subval)) {
                static int num = 0;
                num = num+1;
                std::stringstream stream;
                stream << num;
                std::string name;
                // on utilise une nouvelle variable auxiliaire
                name = "&t" + stream.str();
                archiverra(name, subval);
                ligne = front + name + back;
            }
            else return false;
        }    
    }while(pars);
    return true;
}

// Pour calculer la valeur d'une instruction définie
bool eval(std::string ligne, bigRa& r) {
    if(ligne.size() == 0) return false;
    std::string ops = "^/*-+<>";
    std::size_t found;
    found = ops.find(ligne[ligne.size()-1]);
    // le dernier caractère de ligne ne doit pas être un opérateur
    if(found != std::string::npos) return false;
    if(!parentheses(ligne)) return false;
    if(cval(ligne, r)) return true;
    // ligne[pos] est-il un opérateur ayant 2 opérandes ?
    std::size_t pos=std::string::npos;
    found = ligne.find_last_of("^");
    if(found != std::string::npos) pos=found;
    found = ligne.find_last_of("/");
    if(found != std::string::npos) pos=found;
    found = ligne.find_last_of("*");
    if(found != std::string::npos) pos=found;
    found = ligne.find_last_of("-");
    if(found != std::string::npos) {
        std::size_t pm=found;
        bool bon = true;
        if(pm > 0 && ligne[pm-1] == '^') bon = false;
        if(pm > 0 && ligne[pm-1] == '*') bon = false;
        if(pm > 0 && ligne[pm-1] == '/') bon = false;
        if(pm > 0 && ligne[pm-1] == '+') bon = false;
        while(pm > 0 && ligne[pm-1] == '-') pm = pm-1;
        if(pm > 0 && ligne[pm-1] == '<') bon = false;
        if(pm > 0 && ligne[pm-1] == '>') bon = false;
        if(pm == 0) {
            ligne = "0" + ligne;
            pm = pm+1;
        }
        // bon = true  pour l'opérateur - à deux opérandes
        // bon = false pour l'opérateur - à un seul argument
        if(bon) pos = pm;
    }
    found = ligne.find_last_of("+");
    if(found != std::string::npos) pos=found;
    found = ligne.find_last_of("<");
    if(found != std::string::npos) pos=found;
    found = ligne.find_last_of(">");
    if(found != std::string::npos) pos=found;
    // s'il n'y a ici aucun opérateur : instruction non reconnue
    if(pos == std::string::npos) return false;
    // si un opérateur binaire est au début ou à la fin de ligne
    // l'instruction ne sera pas reconnue
    if(pos==(ligne.size()-1) || pos==0) return false;
    std::string left = ligne.substr(0, pos);
    std::string right = ligne.substr(pos+1);
    // r1 et r2 seront les deux opérandes
    bigRa r1, r2;
    if(!cval(left, r1)) 
        if(!eval(left, r1)) return false;
    if(!cval(right, r2)) 
        if(!eval(right, r2)) return false;
    // calcul final du résultat
    if(ligne[pos] == '^') {
        if(r2.getDen() != 1) {
            aout("l'exposant doit être un entier.\n");
            return false;
		}
        Integer num = r2.getNum();
        int n2;
        if(num > INT_MAX) {
            aout("l'exposant est modifié : il est mis à la limite maximum admise.\n");
            n2 = INT_MAX;
        }
        else if (num < -INT_MAX) {
            aout("l'exposant est modifié : il est mis à la limite minimum admise.\n");
            n2 = -INT_MAX;
        }
        else n2 = num;
        r=r1.puissance(n2);
    }
    if(ligne[pos] == '/') r=r1.diviser(r2);
    if(ligne[pos] == '*') r=r1.multiplier(r2);
    if(ligne[pos] == '-') r=r1.soustraire(r2);
    if(ligne[pos] == '+') r=r1.additionner(r2);
    if(ligne[pos] == '<') r=cmpRa(r2, r1);
    if(ligne[pos] == '>') r=cmpRa(r1, r2);
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


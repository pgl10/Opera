// listera.cpp

#include "listera.hpp"
#include "eval.hpp"

void initra() {       // pour initialiser listera
    listera = NULL;
    return;
}

elemra* chercherra(char* name){  // pour chercher un élément 
    elemra* era;                 // de listera par son nom
    era = listera;
    while(era != NULL) { 
        if(strcmp(era->nom, name) == 0) return era; 
        era = era->suiv;
    }
    return NULL;
}

bool modifierra(std::string st, bigRa& ra) {  // pour mettre à jour la valeur
    elemra* era;                              // d'une variable dans listera
    era = listera;
    char* name = new char[1+st.size()];
    strcpy(name, st.c_str());
    while(era != NULL) { 
        if(strcmp(era->nom, name) == 0) {
            delete era->ra;
            era->ra = new bigRa(ra);
            delete [] name;
            return true;
        }
        era = era->suiv;
    }
    delete [] name;
    return false;
}

bool archiverra(std::string st, bigRa& ra) {  // pour archiver une nouvelle variable
    char* nom = new char[1+st.size()];        // au début de listera
    strcpy(nom, st.c_str());
    elemra* era = chercherra(nom);
    if(era != NULL) {
        aout("Cette variable existe déjà : ce résultat n'est pas archivé.\n");
        delete [] nom;
        return false;
    }
    era = new elemra;
    era->nom = nom;
    era->ra = new bigRa(ra);
    era->suiv = listera;
    listera = era;
    return true;
}

void supprimerra(std::string st) {       // pour supprimer une variable
    char* nom = new char[1+st.size()];   // dans listera
    strcpy(nom, st.c_str());
	if(strcmp(nom, "last") == 0) {
        std::cout << "c'est impossible." << std::endl;
        delete [] nom;
        return;
    }
    // erx : pointeur sur l'élement précédent de era
    elemra* erx = NULL;
    elemra* era = listera;
    while(era != NULL) { 
        if(strcmp(era->nom, nom) == 0) break; 
        erx = era;
        era = era->suiv;
    }
    if(era == NULL) {
        std::cout << "variable inconnue." << std::endl;
        delete [] nom;
        return;
    }
    delete era->nom;
    delete era->ra;
    if(erx == NULL) listera = era->suiv;
    else erx->suiv = era->suiv;
    delete era;
    delete [] nom;
}

bool renommer(std::string& ligne) {    // pour renommer les variables ayant
    bool good;                         // actuellement pour suffixe une variable
    do {                               // dont la valeur est un entier positif ou nul
        good = true;
        std::size_t f1 = ligne.find("[");
        if(f1 == std::string::npos) continue;
        good = false;
        std::size_t f2 = ligne.find("]");
        if(f2 == std::string::npos) return false;
        std::string front = ligne.substr(0, f1);
        std::string back = ligne.substr(f2+1);
        std::string ind = ligne.substr(f1+1, f2-f1-1);
        char* nom = new char[1+ind.size()];
        strcpy(nom, ind.c_str());
        elemra* era = chercherra(nom);
        delete [] nom;
        if(era == NULL) {
            aout("il y a un suffixe dont la variable est inconnue\n");
            return false;
        }
        bigRa ra = *era->ra;
        if(ra.getDen() != 1 || ra.getNum() < 0) {
            aout("il y a un suffixe dont la variable est invalide\n");
            return false;
        }
        std::stringstream ss;
        ss << ra.getNum();
        ligne = front + ss.str() + back;
    }while(!good);
    return true;
}

void lister() {  // pour lister toutes les variables actuelles
    elemra* era = listera;
    while(era != NULL) { 
        std::string name = era->nom;
        bigRa* pra = era->ra;
        // sauf last et les variables auxiliaires
        if(name != "last" && name[0] != '&') std::cout << name << " = " << *pra << std::endl;
        era = era->suiv;
    }
}

//Pour sauvegarder toutes les variables actuelles dans un fichier
void sauvegarder(std::string filename) {
    std::ifstream filein(filename.c_str(), std::ifstream::in);
    if(filein.good()) {
        std::cout << "Le fichier " << filename << " existe : il faut un autre nom." << std::endl;
        filein.close();
        return;
    }  
    std::ofstream fileout(filename.c_str(), std::ofstream::out);
    if(!fileout.good()) {
        aout("Ce fichier n'a pas été créé.\n");
        return;
    }  
    elemra* era = listera;
    while(era != NULL) { 
        std::string name = era->nom;
        bigRa* pra = era->ra;
        // sauf last et les variables auxiliaires
        if(name != "last" && name[0] != '&') fileout << name << " = " << *pra << std::endl;
        era = era->suiv;
    }
    fileout.close();
}


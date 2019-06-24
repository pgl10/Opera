// listera.cpp

#include "listera.hpp"

void initra() {       // pour initialiser listera
    listera = NULL;
    return;
}

void ajouterra(char* name, bigRa& a) {  // pour ajouter un élément
    elemra* era;                        // dans listera
    era = (elemra *)malloc(sizeof(elemra));
    era->nom = name;
    era->ra = new bigRa(a);
    era->suiv = listera;
    listera = era;
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

bool modifierra(char* name, bigRa& a) {  // pour mettre à jour la valeur
    elemra* era;                         // d'un élement de listera
    era = listera;
    while(era != NULL) { 
        if(strcmp(era->nom, name) == 0) {
            delete era->ra;
            era->ra = new bigRa(a);
            return true;
        }
        era = era->suiv;
    }
    return false;
}

void archiver(std::string st, bigRa& ra) {  // pour archiver une
    char* nom = new char[1+st.size()];      // nouvelle variable
    strcpy(nom, st.c_str());
    elemra* era = chercherra(nom);
    if(era != NULL) {
        aout("Cette variable existe déjà : ce résultat n'est pas archivé.\n");
        return;
    }
    ajouterra(nom, ra);
}

void supprimer(std::string st) {         // pour supprimer
    char* nom = new char[1+st.size()];   // une variable
    strcpy(nom, st.c_str());
    // erx : le précédent de era
    elemra* erx = NULL;
    elemra* era = listera;
    while(era != NULL) { 
        if(strcmp(era->nom, nom) == 0) break; 
        erx = era;
        era = era->suiv;
    }
    if(era == NULL) {
        std::cout << "variable inconnue." << std::endl;
        return;
    }
    delete era->nom;
    delete era->ra;
    if(erx == NULL) {
        listera = era->suiv;
        return;
    }
    erx->suiv = era->suiv;
}

void lister() {  // pour lister toutes les variables actuelles
    elemra* era = listera;
    while(era != NULL) { 
        std::string name = era->nom;
        bigRa* pra = era->ra;
        std::cout << name << " = " << *pra << std::endl;
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
        fileout << name << " = " << *pra << std::endl;
        era = era->suiv;
    }
    fileout.close();
}

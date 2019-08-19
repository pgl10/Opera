// listera.cpp

#include "listera.hpp"

void initra() {       // pour initialiser listera
    listera = NULL;
    return;
}

void ajouterra(char* name, bigRa& a) {  // pour ajouter un élément validé
    elemra* era = new elemra;           // au début de liste dans listera
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

bool archiverra(std::string st, bigRa& ra) {  // pour archiver une nouvelle
    char* nom = new char[1+st.size()];        // variable dans listera
    strcpy(nom, st.c_str());
    elemra* era = chercherra(nom);
    if(era != NULL) {
        aout("Cette variable existe déjà : ce résultat n'est pas archivé.\n");
        return false;
    }
    ajouterra(nom, ra);
    return true;
}

void supprimerra(std::string st) {       // pour supprimer une variable
    char* nom = new char[1+st.size()];   // dans listera
    strcpy(nom, st.c_str());
	if(strcmp(nom, "last") == 0) {
        std::cout << "c'est impossible." << std::endl;
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
        return;
    }
    delete era->nom;
    delete era->ra;
    if(erx == NULL) listera = era->suiv;
    else erx->suiv = era->suiv;
    delete era;
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

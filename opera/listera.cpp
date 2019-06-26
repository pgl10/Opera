// listera.cpp

#include "listera.hpp"

void initra() {       // pour initialiser listera
    listera = NULL;
    return;
}

void ajouterra(char* name, bigRa& a) {  // pour ajouter un �l�ment valid�
    elemra* era = new elemra;           // en fin de liste dans listera
    era->nom = name;
    era->ra = new bigRa(a);
    era->suiv = listera;
    listera = era;
    return;
}

elemra* chercherra(char* name){  // pour chercher un �l�ment 
    elemra* era;                 // de listera par son nom
    era = listera;
    while(era != NULL) { 
        if(strcmp(era->nom, name) == 0) return era; 
        era = era->suiv;
    }
    return NULL;
}

bool modifierra(char* name, bigRa& a) {  // pour mettre � jour la valeur
    elemra* era;                         // d'un �lement de listera
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
        aout("Cette variable existe d�j� : ce r�sultat n'est pas archiv�.\n");
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
    // erx : pointeur sur l'�lement pr�c�dent de era
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
        aout("Ce fichier n'a pas �t� cr��.\n");
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

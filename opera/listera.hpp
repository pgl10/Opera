// listera.hpp
#ifndef LISTERA_HPP
#define LISTERA_HPP

#include <string>
#include <fstream>

#include "bigRa.hpp"

void aout(std::string s);

struct elemra {     // structure pour
    char* nom;      // un élément d'archive
    bigRa* ra;      // des variables
    elemra* suiv;   // connues
};

extern elemra* listera;  // archive des bigRa
// Attention : ne pas oublier de faire dans
// le programme principal : elemra* listera;

void initra();
void ajouterra(char* name, bigRa& a);
elemra* chercherra(char* name);
bool modifierra(char* name, bigRa& a);
void archiver(std::string st, bigRa& ra);
void supprimer(std::string st);
void lister();
void sauvegarder(std::string filename);

#endif // LISTERA_HPP

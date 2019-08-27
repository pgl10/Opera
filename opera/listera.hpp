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
elemra* chercherra(char* name);
bool modifierra(std::string st, bigRa& ra);
bool archiverra(std::string st, bigRa& ra);
void supprimerra(std::string st);
bool renommer(std::string& ligne);
void lister();
void sauvegarder(std::string filename);

#endif // LISTERA_HPP

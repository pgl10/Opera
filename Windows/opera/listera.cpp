// listera.cpp

#include "listera.hpp"

Var::~Var() {}

Var::Var() {
    _niv = lect;
    _nom = "";
    _ra = 0;
}

Var::Var(std::string st) {
    _niv = lect;
    _nom = st;
    _ra = 0;
}

Var::Var(const Var& v) : _niv(v._niv), _nom(v._nom), _ra(v._ra) {}

int Var::getNiv() {
    return _niv;
}

std::string Var::getNom() {
    return _nom;
}

bigRa Var::getRa() {
    return _ra;
}

void Var::setNiv(int nv) {
    _niv = nv;
}

void Var::setRa(bigRa ra) {
    _ra = ra;
}

bool Var::operator == (Var r) {
    if((*this).getNiv() != r.getNiv()) return false;
    if((*this).getNom() != r.getNom()) return false;
    if(cmpRa((*this).getRa(),r.getRa()) != 0) return false;
    return true;
}

// Pour chercher la valeur d'une variable connue par son niveau et son nom
bool chercherra(int nv, std::string st, bigRa& ra) {
    for(std::list<Var>::iterator it=listera.begin(); it!=listera.end(); ++it)
        if((*it).getNiv() == nv && (*it).getNom() == st) {
            ra = (*it).getRa();
            return true;
        }
    return false;
}

// Pour modifier la valeur d'une variable connue par son niveau et son nom
bool modifierra(int nv, std::string st, bigRa& ra) {
    for(std::list<Var>::iterator it=listera.begin(); it!=listera.end(); ++it)
        if((*it).getNiv() == nv && (*it).getNom() == st) {
            (*it).setRa(ra);
            return true;
        }
    return false;
}

// Pour archiver une nouvelle variable connue par son niveau, son nom et sa valeur
bool archiverra(int nv, std::string st, bigRa& ra) {
    bigRa x;
    for(std::list<Var>::iterator it=listera.begin(); it!=listera.end(); ++it)
        if((*it).getNiv() == nv && (*it).getNom() == st) {
            x = (*it).getRa();
            return false;
        }
    Var v(st);
    v.setNiv(nv);
    v.setRa(ra);
    listera.push_back(v);
    return true;
}

// Pour supprimer une variable connue par son niveau et son nom
bool supprimerra(int nv, std::string st) {
    for(std::list<Var>::iterator it=listera.begin(); it!=listera.end(); ++it)
        if((*it).getNiv() == nv && (*it).getNom() == st) {
            listera.erase(it);
            return true;
        }
    return false;
}

// Pour renommer les variables ayant pour indice une constante ou une variable
// ou une expression arithmétique dont la valeur actuelle est un entier positif ou nul
// Au k-ième tour du for(;;){} on effectue le traitement du k-ième [...]
bool renommer(std::string& ligne) {
    ligne = "a" + ligne;
    for(int k=1;;k++) {
        std::size_t f1 = 0;
        for(int i=0; i<k; i++) f1 = ligne.find("[", f1+1);
        if(f1 == std::string::npos) break;
        std::size_t f2 = ligne.find("]", f1);
        if(f2 == std::string::npos) return false;
        std::string front = ligne.substr(0, f1);
        std::string back = ligne.substr(f2+1);
        std::string indic = ligne.substr(f1+1, f2-f1-1);
        if(isnumb(indic)) continue;
        int nb;
        if(!ival(indic, nb)) return false;
        std::stringstream ss;
        ss << nb;
        ligne = front + "[" + ss.str() + "]" + back;
    }
    ligne = ligne.substr(1);
    return true;
}

// transv.cpp

#include "transv.hpp"

// La classe Trans concerne la transmission des variables en arguments
// d'un fichier de commandes qui en appelle un autre.

Trans::~Trans() {}

Trans::Trans(std::string f) {
    _niv = lect;
    _fic = f;
}

void Trans::setNiv(int nv) {
    _niv = nv;
}

int Trans::getNiv() {
    return _niv;
}

std::string Trans::getFic() {
    return _fic;
}

std::vector<std::string> Trans::getOld() {
    return _old;
}

std::vector<std::string> Trans::getNew() {
    return _new;
}

std::vector<unsigned int> Trans::getIndic() {
    return _indic;
}

void Trans::setOld(std::vector<std::string> vs) {
    _old = vs;
}

void Trans::setNew(std::vector<std::string> vs) {
    _new = vs;
}

void Trans::setIndic(std::vector<unsigned int> vui) {
    _indic = vui;
}

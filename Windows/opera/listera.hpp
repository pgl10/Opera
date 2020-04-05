// listera.hpp
#ifndef LISTERA_HPP
#define LISTERA_HPP

#include <list>
#include <string>
#include "bigRa.hpp"
#include "eval.hpp"

class Var {
private:
    int _niv;
    std::string _nom;
    bigRa _ra;
public:
    ~Var();
    Var();
    Var(std::string st);
    Var(const Var& v);
    int getNiv();
    std::string getNom();
    bigRa getRa();
    void setNiv(int nv);
    void setRa(bigRa ra);
    bool operator == (Var r);
};

extern int lect;
extern std::list<Var> listera;

bool chercherra(int nv, std::string st, bigRa& ra);
bool modifierra(int nv, std::string st, bigRa& ra);
bool archiverra(int nv, std::string st, bigRa& ra);
bool supprimerra(int nv, std::string st);
bool renommer(std::string& ligne);

#endif // LISTERA_HPP

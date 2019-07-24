// bigRa.hpp
#ifndef BIGRA_HPP
#define BIGRA_HPP

#include <iostream>
#include <sstream> 
#include <string>
#include "Integer.h"

class bigRa {
  private :
    Integer _num;
    Integer _den;
  public :
    bigRa();
    bigRa(int nume);
    bigRa(int nume, int deno);
    bigRa(Integer nume);
    bigRa(Integer nume, Integer deno);
    bigRa(char* nume);
    bigRa(char* nume, char* deno);
    bigRa(bigRa& a);
    ~bigRa(void);
    
    void setNum(int nume);
    void setDen(int deno);
    void setNum(Integer nume);
    void setDen(Integer deno);
    void setNum(char* nume);
    void setDen(char* deno);

    Integer getNum();
    Integer getDen();

    bigRa operator - () const;
    bigRa operator = (bigRa& a);
    bigRa operator = (int n);

    void simplifier();

    bigRa additionner(bigRa& x) const;
    bigRa soustraire(bigRa& x) const;
    bigRa multiplier(bigRa& x) const;
    bigRa diviser(bigRa& x) const;
    bigRa puissance(int n) const;
};

bigRa operator + (bigRa& l, bigRa& r);
bigRa operator - (bigRa& l, bigRa& r);
bigRa operator * (bigRa& l, bigRa& r);
bigRa operator / (bigRa& l, bigRa& r);
bigRa operator ^ (bigRa& l, bigRa& r);
bigRa operator ^ (bigRa& l, int r);

std::ostream& operator << (std::ostream& ost, bigRa& a);
std::istream& operator >> (std::istream& ist, bigRa& a);

Integer entier(bigRa a);
bigRa pfract(bigRa a);
int cmpRa(bigRa a, bigRa b);
bool isEnti(bigRa a);
bigRa inverser(bigRa a);
double reel(bigRa a);

#endif // BIGRA_HPP

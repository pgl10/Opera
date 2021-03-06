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
    bigRa(const bigRa& a);
    ~bigRa(void);
    
    void setNum(int nume);
    void setDen(int deno);
    void setNum(Integer nume);
    void setDen(Integer deno);
    void setNum(char* nume);
    void setDen(char* deno);

    Integer getNum() const;
    Integer getDen() const;

    bigRa operator - () const;
    bigRa operator = (const bigRa& a);
    bigRa operator = (int n);

    void simplifier();

    bigRa additionner(bigRa& x) const;
    bigRa soustraire(bigRa& x) const;
    bigRa multiplier(bigRa& x) const;
    bigRa diviser(bigRa& x) const;
    bigRa puissance(int n) const;
};

bigRa operator + (const bigRa& l, const bigRa& r);
bigRa operator - (const bigRa& l, const bigRa& r);
bigRa operator * (const bigRa& l, const bigRa& r);
bigRa operator / (const bigRa& l, const bigRa& r);
bigRa operator ^ (const bigRa& l, const bigRa& r);
bigRa operator ^ (const bigRa& l, int r);

std::ostream& operator << (std::ostream& ost, const bigRa& a);
std::istream& operator >> (std::istream& ist, bigRa& a);

Integer entier(bigRa a);
bigRa pfract(bigRa a);
int cmpRa(bigRa a, bigRa b);
bool isEnti(bigRa a);
bigRa inverser(bigRa a);
double ra2dbl(bigRa x);
double root(bigRa x, int n, int k);
bigRa nroot(bigRa x, int n, int k);
bigRa dbl2ra(double x);

#endif // BIGRA_HPP

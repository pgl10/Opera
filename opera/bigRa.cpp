// bigRa.cpp

#include "bigRa.hpp"

// premier constructeur
bigRa::bigRa() {
    _num = 0;
    _den = 1;
}

bigRa::bigRa(int nume) {
    _num = nume;
    _den = 1;
}

bigRa::bigRa(int nume, int deno) {
    if(deno < 0) {
        _num = -nume;
        _den = -deno;
    }
    else {
        _num = nume;
        _den = deno;
    }
}

bigRa::bigRa(Integer nume) {
    _num = nume;
    _den = 1;
}

bigRa::bigRa(Integer nume, Integer deno) {
    if(deno < 0) {
        _num = -nume;
        _den = -deno;
    }
    else {
        _num = nume;
        _den = deno;
    }
}

bigRa::bigRa(char* nume) {
    _num = nume;
    _den = 1;
}

// septième constructeur
bigRa::bigRa(char* nume, char* deno) {
    _num = nume;
    _den = deno;
    if(_den < 0) {
        _num = -_num;
        _den = -_den;
    }
}

// constructeur de recopie
bigRa::bigRa(bigRa& a) : _num(a._num), _den(a._den) {}

// destructeur
bigRa::~bigRa() {}

void bigRa::setNum(int nume) { 
    _num = nume;
}

void bigRa::setDen(int deno) {
    _den = deno;
    if(_den < 0) {
        _num = -_num;
        _den = -_den;
    }
}

void bigRa::setNum(Integer nume) { 
    _num = nume;
}

void bigRa::setDen(Integer deno) {
    _den = deno;
    if(_den < 0) {
        _num = -_num;
        _den = -_den;
    }
}

void bigRa::setNum(char* nume) { 
    _num = nume;
}

void bigRa::setDen(char* deno) {
    _den = deno;
    if(_den < 0) {
        _num = -_num;
        _den = -_den;
    }
}

Integer bigRa::getNum() {
    return _num;
}

Integer bigRa::getDen() {
    return _den;
}

bigRa bigRa::operator - () const {
    bigRa t;
    if(_num == 0) {
        t._num = 0;
        t._den = 1;
    }
    else {
        t._num = -Integer(_num);
        t._den = _den;
    }
    return t;
}

bigRa bigRa::operator = (bigRa& a) {
    _num = a._num;
    _den = a._den;
    return *this;
}

bigRa bigRa::operator = (int n) {
    _num = n;
    _den = 1;
    return *this;
}

void bigRa::simplifier() {
    if(_num == 0) {
        // simplifier : 0/d  =>  0/1 (c'est à dire : 0)
        // si d = 0 on fait aussi 0/1 arbitrairement
        // sans aucun message d'avertissement !
        _den = 1;
        return;
    }
    if(_den < 0) {
        _num = -_num;
        _den = -_den;
    }
    if(_den != 1) {
        Integer x;
        x = gcd(_num, _den);
        // ce calcul est toujours correct même
        // si : _den = 0 (ici _num est non nul)
        _num = _num/x;
        _den = _den/x;
    }
}

bigRa bigRa::additionner(bigRa& x) const {
  bigRa t;
  if(_den == x.getDen()) {
    t.setNum(_num + x.getNum());
    t.setDen(x.getDen());
  }
  else {
    t.setNum(_num * x.getDen() + _den * x.getNum());
    t.setDen(_den * x.getDen());
  }
  t.simplifier();
  return t;
}

bigRa bigRa::soustraire(bigRa& x) const {
  bigRa t;
  if(_den == x.getDen()) {
    t.setNum(_num - x.getNum());
    t.setDen(x.getDen());
  }
  else {
    t.setNum(_num * x.getDen() - _den * x.getNum());
    t.setDen(_den * x.getDen());
  }
  t.simplifier();
  return t;
}

bigRa bigRa::multiplier(bigRa& x) const {
  bigRa t;
  t._num = _num * x.getNum();
  t._den = _den * x.getDen();
  t.simplifier();
  return t;
}

bigRa bigRa::diviser(bigRa& x) const {
  bigRa t;
  t._num = _num * x.getDen();
  t._den = _den * x.getNum();
  t.simplifier();
  return t;
}

// calcul de t^n (n positif ou nul)
bigRa fnctp(bigRa t, int n) {
    bigRa r;
    if(n > 2) {
        bigRa x = fnctp(t, n/2);
        if((n&1) == 0) r = x*x;
        else r = x*x*t;
    }
    else if(n == 0) r = bigRa(1);
    else if(n == 1) r = t;
    else if(n == 2) r = t*t;
    return r;
}

bigRa bigRa::puissance(int n) const {
  bigRa t = bigRa(_num, _den), x;
  int m = n;
  if(n < 0) {t = inverser(t); m=-n;}
  t.simplifier();
  x = fnctp(t, m);
  return x;
}

bigRa operator + (bigRa& l, bigRa& r) {
  bigRa t = l.additionner(r);
  return t;
}

bigRa operator - (bigRa& l, bigRa& r) {
  bigRa t = l.soustraire(r);
  return t;
}

bigRa operator * (bigRa& l, bigRa& r) {
  bigRa t = l.multiplier(r);
  return t;
}

bigRa operator / (bigRa& l, bigRa& r) {
  bigRa t = l.diviser(r);
  return t;
}

bigRa operator ^ (bigRa& l, bigRa& r) {
  bigRa t = l.puissance(entier(r));
  return t;
}

bigRa operator ^ (bigRa& l, int r) {
  bigRa t = l.puissance(r);
  return t;
}

std::ostream& operator << (std::ostream& ost, bigRa& a) {
    a.simplifier();
    if(a.getDen() == 1) ost << a.getNum();
    else ost << a.getNum() << "/" << a.getDen();
    return ost;
}

std::istream& operator >> (std::istream& ist, bigRa& a) {
    std::string st;
    ist >> st;
    std::size_t found;
    found = st.find('/');
    if(found == std::string::npos) {
        std::istringstream iss;
        iss.str(st);
        Integer n;
        iss >> n;
        a = bigRa(n);
    }
    else {
        std::istringstream issn, issd;
        issn.str(st.substr(0, found));
        issd.str(st.substr(found+1));
        Integer n, d;
        issn >> n;
        issd >> d;
        a = bigRa(n, d);
    }
    a.simplifier();
    return ist;
}

// Partie entière de a
Integer entier(bigRa a) {
    a.simplifier();
    Integer n, d = a.getDen();
    if(d == 0) n = 0;
    else n = a.getNum()/d;
    return n;
}

// Partie fractionnaire de a
bigRa pfract(bigRa a) {
    a.simplifier();
    bigRa n = bigRa(entier(a));
    bigRa r = a.soustraire(n);
    return r;
}

// Comparer 2 bigRa ( a<b : -1 | a=b : 0 | a>b : 1 )
// Exemple : if(cmpRa(a, b) > 0) pour : si a > b
int cmpRa(bigRa a, bigRa b) {
    a.simplifier();
    b.simplifier();
    if(a.getDen() == 0 && b.getDen() == 0) {
        if(a.getNum() < b.getNum()) return -1;
        if(a.getNum() == b.getNum()) return 0;
        return 1;
    }
    if(a.getDen() == 0) {
        if(a.getNum() < 0) return -1;
        return 1;
    }
    if(b.getDen() == 0) {
        if(b.getNum() > 0) return -1;
        return 1;
    }
    Integer na = a.getNum() * b.getDen();
    Integer nb = b.getNum() * a.getDen();
    if(na < nb) return -1;
    if(na == nb) return 0;
    return 1;
}

// Est-ce que a est un nombre entier ?
bool isEnti(bigRa a) {
    a.simplifier();
    if(a.getDen() == 1) return true;
    return false;
}

// Inverser un bigRa
bigRa inverser(bigRa a) {
    bigRa r;
	if(a.getNum() < 0) {
    r.setDen(-a.getNum());
    r.setNum(-a.getDen());
    }
	else {
    r.setDen(a.getNum());
    r.setNum(a.getDen());
    }
    r.simplifier();
    return r;
}

// Pour convertir en double un bigRa ayant son numérateur 
// et son dénominateur plus petits que 10^308
double reel(bigRa a) {
    double r = double(a.getNum())/double(a.getDen());
    return r;
}

// Pour convertir un bigRa en double
double ra2d(bigRa x) {
    int lim = 64;
    Integer num = x.getNum();
    Integer den = x.getDen();
    std::stringstream sn;
    sn << num;
    std::stringstream sd;
    sd << den;
    int nn = sn.str().size();
    int nd = sd.str().size();
    if(nn<lim && nd<lim) return double(num)/double(den);
    int mn = nn - lim;
    if(mn > nd - lim) mn = nd - lim;
    if(mn < 0) mn = 0;
    nn = nn - mn;
    nd = nd - mn;
    num = sn.str().substr(0, nn).c_str();
    den = sd.str().substr(0, nd).c_str();
    return double(num)/double(den);
}

// Pour calculer en double une approximation r 
// de la n-ième racine de x telle que : |x-r^n| < x/10^k
double root(bigRa x, int n, int k) {
    double a = ra2d(x);
    if(a < 0) return 0.0;
    if(n < 2) return 0.0;
    if(k < 1) return 0.0;
    double dk = 1.0;
    for(int i=0; i<k; i++) dk=dk*10.0;
    double n1 = n-1, r = 1.0, rn = 1.0, dif;
    do {
        double rn1 = rn/r;
        r = (n1*r+a/rn1)/double(n);
        rn = 1.0;
        for(int i=0; i<n; i++) rn=rn*r;
        dif = abs(a - rn);
    }while(dif > a/dk);
    return r;
}

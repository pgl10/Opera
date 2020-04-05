// transv.hpp
#ifndef TRANSV_HPP
#define TRANSV_HPP

#include <list>
#include <vector>
#include <string>

class Trans {
private:
    int _niv;
    std::string _fic;
    std::vector<std::string> _old;
    std::vector<std::string> _new;
    std::vector<unsigned int> _indic;
public:
    ~Trans();
    Trans(std::string f);
    void setNiv(int nv);
    int getNiv();
    std::string getFic();
    std::vector<std::string> getOld();
    std::vector<std::string> getNew();
    std::vector<unsigned int> getIndic();
    void setOld(std::vector<std::string> vs);
    void setNew(std::vector<std::string> vs);
    void setIndic(std::vector<unsigned int> vui);
};

extern int lect;

#endif // TRANSV_HPP

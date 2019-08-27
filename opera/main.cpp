/*******************************************************************************
*  Opera : calculs arithmétiques avec des nombres rationnels de grande taille  *
*  On a ici les 5 opérations de base  -  par : pgl10  -   utilisation : Opera  *              
*******************************************************************************/

#include "main.hpp"

void pause() {
    std::cout << std::endl;
    system("pause");    
}

void aide() {
    aout("\nOpera utilise les 7 opérateurs binaires :  ^  /  *  -  +  <  >   \n");
    aout("avec cet ordre de priorité et l'opérateur - ayant un seul opérande.\n");
    aout("Les instructions admises sont : > e ou bien : > v = e où e : entier\n");
    aout(" ou nombre décimal, ou variable, ou expression arithmétique valide.\n");
    aout("> ilyatil v | > del v | > out sauv.txt | > exec fic.txt | > conv e \n");
    aout("Avec des entiers > pgcd e1,e2 | > ppcm e1,e2 | > prem e | > ndiv e \n");
    aout("> enti e | > frac e | > num e | > den e | > liste | > aide | > exit\n");
}    

int main(int argc, char *argv[]) {
    aout("\nCalculs arithmétiques avec des nombres rationnels de grande taille\n");
    // filesin[i] utilisable avec i de 1 à 9
    std::ifstream filesin[10];
    int lect = 0;
    if(argc == 2) {
        filesin[1].open(argv[1]);
        if(!filesin[1].good()) {
            std::cout << "\nLe fichier " << argv[1] << " n'est pas disponible.\n";
            pause();
            return 1;
        }
        lect = 1;
    }
    if(argc > 2) {
        std::cout << "\nFaire : opera.exe ou bien : opera fichier.txt\n";
        pause();
        return 1;
    }
    if(lect == 0) {
        aout("Pour le mode d'emploi consulez le fichier emploi.txt\n");
        aout("Pour une aide immédiate entrez : aide\n");
    }
    initra();
    archiverra("last", bigRa(0));
    std::streamoff back, here=0;
    std::vector<std::streamoff> ret;
    bool modif = false;
        for(;;) {
        std::string ligne;
        if(lect > 0) {
            back = here;
            here = filesin[lect].tellg();
            std::getline(filesin[lect], ligne);
            if(!filesin[lect].good()) {
                filesin[lect].close();
                lect = lect - 1;
                continue;
            }
            else {
                std::cout << "\n> ";
                aout(ligne);
                std::cout << std::endl;
            }
        }
        else {
            std::cout << "\n> ";
            std::getline(std::cin, ligne);
        }
        outspaces(ligne);
        if(!renommer(ligne)) continue;
        if(ligne[0] == '#') continue;
        if(ligne == "exit") break;
        if(ligne == "aide") {
            aide();
            continue;
        }
        if(ligne.size() > 3 && ligne.substr(0, 3) == "del") {
            supprimerra(ligne.substr(3));
            continue;
        }
        if(ligne == "liste") {
            lister();
            continue;
        }
        if(ligne.size() > 3 && ligne.substr(0, 3) == "out") {
            sauvegarder(ligne.substr(3));
            continue;
        }    
        if(ligne.size() > 4 && ligne.substr(0, 4) == "exec") {
            ligne = ligne.substr(4);
            if(lect == 9) {
                std::cout << "Le fichier de commandes actuel ne peut pas en utiliser un autre.\n";
                continue;
            }
            filesin[lect+1].open(ligne.c_str());
            if(!filesin[lect+1].good()) {
                std::cout << "Le fichier " << ligne.c_str() << " n'est pas disponible.\n";
                continue;
            }
            lect = lect + 1;
            continue;
        }   
        if(ligne == "silast") {
            if(lect == 0) continue;
            elemra* era = chercherra("last");
            if(cmpRa(*era->ra, bigRa(0)) > 0) continue;
            filesin[lect].close();
            lect = lect - 1;
            continue;
        }
        if(ligne == "boucle") {
            if(lect == 0) continue;
            // si cette boucle n'est pas déjà notée : on la note
            if((ret.size() == 0) || (ret.size() != 0 && ret[ret.size()-1] != back)) ret.push_back(back);
            // si l'instruction précédente est une condition positive : on continue
            elemra* era = chercherra("last");
            if(cmpRa(*era->ra, bigRa(0)) > 0) continue;
            // si non : on efface la note et on va après son retour correspondant
            else {
                ret.pop_back();
                int nret = 1;
                do {
                    std::getline(filesin[lect], ligne);
                    outspaces(ligne);
                    if(!filesin[lect].good()) {
                        aout("Le retour est absent : abandon du fichier\n");
                        filesin[lect].close();
                        lect = lect - 1;
                        break;
                    }
                    if(ligne == "boucle") nret = nret + 1;
                    if(ligne == "retour") nret = nret - 1;
                }while(!(ligne == "retour" && nret == 0));
                continue;
            }
        }
        if(ligne == "retour") {
            if(lect == 0) continue;
            if(ret.size() == 0) continue;
            filesin[lect].seekg(ret.back());
            continue;
        }
        if(ligne.size() > 5 && ligne.substr(0, 5) == "modif") {
            ligne = ligne.substr(5);
            if(ligne == "=oui") modif = true;
            else if(ligne == "=non") modif = false;
            else aout("instruction non reconnue.\n");
            continue;
        }
        if(ligne.size() > 4 && ligne.substr(0, 4) == "conv") {
            ligne = ligne.substr(4);
            double r;
            bool good = rval(ligne, r);
            if(!good) aout("conversion impossible.\n");
            else {
                std::cout << std::setprecision(10) << r << std::endl;
                bigRa x;
                if(eval(ligne, x)) modifierra("last", x);
            }
            continue;
        }
        if(ligne.size() > 4 && ligne.substr(0, 4) == "enti") {
            ligne = ligne.substr(4);
            Integer n;
            bool good = nval(ligne, n);
            if(!good) aout("calcul impossible.\n");
            else {
                std::cout << n << std::endl;
                modifierra("last", bigRa(n));
            }
            continue;
        }
        if(ligne.size() > 4 && ligne.substr(0, 4) == "frac") {
            ligne = ligne.substr(4);
            Integer n;
            bool good = nval(ligne, n);
            if(!good) aout("calcul impossible.\n");
            else {
                bigRa x;
                eval(ligne, x);
                bigRa r = x - bigRa(n);
                std::cout << r << std::endl;
                modifierra("last", r);
            }
            continue;
        }
        if(ligne.size() > 3 && ligne.substr(0, 3) == "num") {
            ligne = ligne.substr(3);
            bigRa p;
            bool good = eval(ligne, p);
            if(!good) aout("calcul impossible.\n");
            else {
                std::cout << p.getNum() << std::endl;
                modifierra("last", bigRa(p.getNum()));
            }
            continue;
        }
        if(ligne.size() > 3 && ligne.substr(0, 3) == "den") {
            ligne = ligne.substr(3);
            bigRa q;
            bool good = eval(ligne, q);
            if(!good) aout("calcul impossible.\n");
            else {
                std::cout << q.getDen() << std::endl;
                modifierra("last", bigRa(q.getDen()));
            }
            continue;
        }
        if(ligne.size() > 7 && ligne.substr(0, 7) == "ilyatil") {
            ligne = ligne.substr(7);
             char* nom = new char[1+ligne.size()];
             strcpy(nom, ligne.c_str());
             elemra* era = chercherra(nom);
             delete [] nom;
             if(era != NULL) {
                 std::cout << "last = 1" << std::endl;
                 modifierra("last", bigRa(1));
             }
             else {
                 std::cout << "last = 0" << std::endl;
                 modifierra("last", bigRa(0));
             }
             continue;
        }
        if(ligne.size() > 4 && ligne.substr(0, 4) == "pgcd") {
            ligne = ligne.substr(4);
            std::size_t fv = ligne.find(",");
            if(fv == std::string::npos || fv==(ligne.size()-1) || fv==0) {
                aout("instruction non reconnue.\n");
                continue;
            }
            std::string left = ligne.substr(0, fv);
            std::string right = ligne.substr(fv+1);
            bigRa r1, r2;
            if(!(eval(left, r1) && eval(right,r2))) {
                aout("instruction non reconnue.\n");
                continue;
            }
            if(!(isEnti(r1) && isEnti(r2))) {
                aout("il faut deux entiers.\n");
                aout("instruction invalide.\n");
                continue;
            }
            Integer r = gcd(r1.getNum(), r2.getNum());
            std::cout << r << std::endl;
            modifierra("last", bigRa(r));
            continue;
        }
        if(ligne.size() > 4 && ligne.substr(0, 4) == "ppcm") {
            ligne = ligne.substr(4);
            std::size_t fv = ligne.find(",");
            if(fv == std::string::npos || fv==(ligne.size()-1) || fv==0) {
                aout("instruction non reconnue.\n");
                continue;
            }
            std::string left = ligne.substr(0, fv);
            std::string right = ligne.substr(fv+1);
            bigRa r1, r2;
            if(!(eval(left, r1) && eval(right,r2))) {
                aout("instruction non reconnue.\n");
                continue;
            }
            if(!(isEnti(r1) && isEnti(r2))) {
                aout("il faut deux entiers.\n");
                aout("instruction invalide.\n");
                continue;
            }
            Integer i1, i2, n, d, r;
            i1 = r1.getNum();
            i2 = r2.getNum();
            d = gcd(i1, i2);
            if(d == 0) r = 0;
            else {
                n = i1*i2;
                if(n < 0) n = -n;
                r = n/d;
            }
            std::cout << r << std::endl;
            modifierra("last", bigRa(r));
            continue;
        }
        if(ligne.size() > 4 && ligne.substr(0, 4) == "prem") {
            ligne = ligne.substr(4);
            bigRa x;
            if(!eval(ligne, x)) {
                aout("instruction non reconnue.\n");
                continue;
            }
            if(!isEnti(x)) {
                aout("il faut un entier.\n");
                aout("instruction invalide.\n");
                continue;
            }
            Integer n = x.getNum();
            int r = 1;
            if(!isprime(n)) r = 0;
            std::cout << r << std::endl;
            modifierra("last", bigRa(r));
            continue;
        }
        if(ligne.size() > 4 && ligne.substr(0, 4) == "ndiv") {
            ligne = ligne.substr(4);
            bigRa x;
            if(!eval(ligne, x)) {
                aout("instruction non reconnue.\n");
                continue;
            }
            if(!isEnti(x)) {
                aout("il faut un entier.\n");
                aout("instruction invalide.\n");
                continue;
            }
            Integer r = x.getNum();
            if(r < 0) r = -r;
            if(!isprime(r)) r = get_factor(r);
            std::cout << r << std::endl;
            modifierra("last", bigRa(r));
            continue;
        }
        std::size_t found = ligne.find("=");
        if(found == std::string::npos) {
            if(ligne == "") continue;
            else {
                bigRa ra;
                if(isname(ligne.c_str())) {
                    bool good = vval(ligne, ra);
                    if(good) {
                        std::cout << ligne << " = " << ra << std::endl;
                        modifierra("last", ra);
                    }
                    else std::cout << "variable inconnue." << std::endl;
                    continue;
                }
                else {
                    bool good = eval(ligne, ra);
                    if(good) {
                        std::cout << ligne << " = " << ra << std::endl;
                        modifierra("last", ra);
                    }
                    else aout("instruction non reconnue.\n");
                    continue;
                }
            }
        }    
        else {
            std::string res = ligne.substr(0, found);
            ligne = ligne.substr(found+1);
            if(res != "" && ligne != "") {
                if(isname(res.c_str())) {
                    bigRa ra;
                    if(isname(ligne.c_str())) {
                        bool good = vval(ligne, ra);
                        if(good) {
                            if(modif) {
                                char* nom = new char[1+res.size()];
                                strcpy(nom, res.c_str());
                                elemra* era = chercherra(nom);
                                if(era != NULL) {
                                    if(modifierra(nom, ra)) {
                                        std::cout << res << " = " << ra << std::endl;
                                        modifierra("last", ra);
                                    }
                                    else continue;
                                }
                                else {
                                    if(archiverra(res, ra)) {
                                        std::cout << res << " = " << ra << std::endl;
                                        modifierra("last", ra);
                                    }
                                    else continue;
                                }
                                delete [] nom;
                            }
                            else {
                                if(archiverra(res, ra)) {
                                    std::cout << res << " = " << ra << std::endl;
                                    modifierra("last", ra);
                                }
                                else continue;
                            }
                        }
                        else std::cout << "variable inconnue." << std::endl;
                        continue;
                    }
                    else {
                        bool good = eval(ligne, ra);
                        if(good) {
                            if(modif) {
                                char* nom = new char[1+res.size()];
                                strcpy(nom, res.c_str());
                                elemra* era = chercherra(nom);
                                if(era != NULL) {
                                    if(modifierra(nom, ra)) {
                                        std::cout << res << " = " << ra << std::endl;
                                        modifierra("last", ra);
                                    }
                                    else continue;
                                }
                                else {
                                    if(archiverra(res, ra)) {
                                        std::cout << res << " = " << ra << std::endl;
                                        modifierra("last", ra);
                                    }
                                    else continue;
                                }
                                delete [] nom;
                            }
                            else {
                                if(archiverra(res, ra)) {
                                    std::cout << res << " = " << ra << std::endl;
                                    modifierra("last", ra);
                                }
                                else continue;
                            }
                        }
                        else aout("instruction non reconnue.\n");
                        continue;
                    }
                }
                else {
                    std::cout << "instruction invalide." << std::endl;
                    aide();
                    continue;
                }
            }
            else {
                std::cout << "instruction invalide." << std::endl;
                aide();
                continue;
            }
        }
    }
    return 0;
}

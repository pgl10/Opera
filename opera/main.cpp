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
    aout("\nopera : les seules commandes valides sont de type : \n");
    aout("> a = 1234567890 ( nombre entier de longueur et signe quelconques )\n");
    aout("> b = 123 / 4567 ( num et den de longueurs et signes quelconques. )\n");
    aout("> n = a ? b  ( où ? est un opérateur :  +   -   *   /   ^   >   < )\n");
    aout("> a ? b (ou a seulement) (variables ou constantes) pour un calcul.\n");
    aout("> del v : supprimer v | > out sauv.txt | > exec fic.txt | > liste \n");
    aout("> conv v | enti v | num v | den v | aide | > exit : (var. perdues)\n");
}    

int main(int argc, char *argv[]) {
    aout("\nCalculs arithmétiques avec des nombres rationnels de grande taille\n");
    std::ifstream filein;
    int lect = 0;
    if(argc == 2) {
        filein.open(argv[1]);
        if(!filein.good()) {
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
    for(;;) {
        std::string ligne;
        if(lect == 1) {
            std::getline(filein, ligne);
            if(!filein.good()) {
                lect = 0;
                filein.close();
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
            if(lect != 0) {
                std::cout << "Un fichier de commandes ne peut pas en utiliser un autre.\n";
                continue;
            }
            filein.open(ligne.c_str());
            if(!filein.good()) {
                std::cout << "Le fichier " << ligne.c_str() << " n'est pas disponible.\n";
                continue;
            }
            lect = 1;
            continue;
        }    
        if(ligne.size() > 4 && ligne.substr(0, 4) == "conv") {
            ligne = ligne.substr(4);
            double r;
            bool good = rval(ligne, r);
            if(!good) aout("conversion impossible.\n");
            else std::cout << r << std::endl;
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
                            if(archiverra(res, ra)) {
                                std::cout << res << " = " << ra << std::endl;
                                modifierra("last", ra);
                            }
                            else continue;
                        }
                        else std::cout << "variable inconnue." << std::endl;
                        continue;
                    }
                    else {
                        bool good = eval(ligne, ra);
                        if(good) {
                            if(archiverra(res, ra)) {
                                std::cout << res << " = " << ra << std::endl;
                                modifierra("last", ra);
                            }
                            else continue;
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

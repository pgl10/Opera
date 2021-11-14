/*******************************************************************************
*  Opera : calculs arithmétiques avec des nombres rationnels de grande taille  *
*       par : pgl10   -   utilisation : opera  ou : opera fichier.txt          *
*******************************************************************************/

#include "main.hpp"

int lect = 0;
std::list<Var> listera;
std::list<Trans> listetrv;
// listetrv est une liste de Trans. 
// La première pour le niveau 1 de fonctionnement ... La dernière pour le
// niveau actuel de fonctionnement. En mode conversationnel listetrv est vide.

void aide() {
    aout("\nOpera utilise les 7 opérateurs binaires :  ^  /  *  -  +  <  >   \n");
    aout("avec cet ordre de priorités et l'opérateur - ayant un seul opérande.\n");
    aout("Les constantes admises sont les nombres entiers et les nombres décimaux.\n");
    aout("Opera effectue des expressions arithmétiques et les commandes suivantes :\n");
    aout("exec, copier, renvoyer, prochain, recevoir, envoyer, supprimer, aide, pause,\n");
    aout("lister, noter, garder, lire, valeur, nbch, enti, frac, num, den, continuer,\n");
    aout("quitter, si, boucle, retour, exit, reste, pgcd, ppcm, hasard, facteur, prem,\n");
    aout("invmod, expmod, pnps.\n");
}    

void fermeture() {
    // Pour supprimer toutes les variables locales du niveau actuel 
    std::list<Var>::iterator vt;
    bool done = false;
    while(!done) {
        done = true;
        for(std::list<Var>::iterator it=listera.begin(); it!=listera.end(); ++it)
            if((*it).getNiv() == lect) {
                vt = it;
                done = false;
            }
        if(!done) listera.erase(vt);
    }
    // Pour supprimer la transmission de variables devenue inutile
    listetrv.pop_back();
    // Pour aller au niveau précédent
    if(lect > 0) lect = lect - 1;
}

int main(int argc, char *argv[]) {
    aout("\nCalculs arithmétiques avec des nombres rationnels de grande taille\n");
    // filesin[i] utilisable avec i de 1 à 9 pour les niveaux 1 à 9 de fonctionnement.
    std::ifstream filesin[10];
    // copier = true par l'instruction "exec" pour autoriser l'instruction "copier"
    // copier = false par l'instruction "copier" pour "copier" en premier uniquement.
    bool copier = false;
    bigRa br0 = bigRa(0);
    archiverra(0, "last", br0);
    if(argc == 2) {
        filesin[1].open(argv[1]);
        if(!filesin[1].good()) {
            std::cout << "\nLe fichier " << argv[1] << " n'est pas disponible.\n";
            pause();
            return 1;
        }
        lect = 1;
        archiverra(1, "last", br0);
        std::string file = argv[1];
        Trans tr0(file);
        tr0.setNiv(1);
        listetrv.push_back(tr0);
	}
        if(argc > 2) {
        std::cout << "\nFaire : opera.exe ou bien : opera fichier.txt\n";
        pause();
        return 1;
    }
    if(lect == 0) {
        aout("Pour le mode d'emploi consultez le fichier Opera.pdf\n");
        aout("Pour une aide immédiate entrez : aide\n");
    }
    std::vector<std::streamoff> ret;
    std::streamoff back, here=-1;
    bool jump = false;
    for(;;) {
        std::string ligne;
        if(lect > 0) {
            back = here;
            here = filesin[lect].tellg();
            std::getline(filesin[lect], ligne);
            if(jump) {
                back = here;
                here = filesin[lect].tellg();
                std::getline(filesin[lect], ligne);
                jump = false;
            }
            if(!filesin[lect].good()) {
                filesin[lect].close();
                fermeture();
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
        firstspaces(ligne);
        if(ligne[0] == '#') continue;
        delcom(ligne);
        if(!renommer(ligne)) {
            aout("Cette instruction n'est pas effectuée : indice invalide.\n");
            continue;
        }
        // cmde : l'instruction actuelle sans les premiers ' ' et sans commentaire
        std::string cmde = ligne;
        // line : le premier mot de l'instruction actuelle
        std::string line = ligne;
        premiermot(line);
        // ligne : l'instruction actuelle sans aucun ' '
        outspaces(ligne);
        // Pour supprimer toutes les variables temporaires actuelles du niveau actuel 
        std::list<Var>::iterator vt;
        bool done = false;
        while(!done) {
            done = true;
            for(std::list<Var>::iterator it=listera.begin(); it!=listera.end(); ++it)
                if((*it).getNiv() == lect && (*it).getNom()[0] == '&') {
                    vt = it;
                    done = false;
                }
            if(!done) listera.erase(vt);
        }
        // L'instruction "copier" est nécessairement la première d'un fichier de commandes
        if(copier && keywd(line, ligne, "copier")) {
            if(lect == 0) continue;
            char* chrs = new char[1+cmde.size()];
            unsigned int i;
            for(i=0; i<cmde.size(); i++) {
                if(cmde[i] != ',') chrs[i] = cmde[i];
                else chrs[i] = ' ';
            }
            chrs[i] = '\0';
            std::string cmdn = std::string(chrs);
            delete [] chrs;
            std::stringstream ss(cmdn);
            std::string verbe;
            ss >> verbe;
            Trans tr = listetrv.back();
            unsigned int nbv = 0;
            std::vector<std::string> vs;
            for(;;) {
                std::string var;
                ss >> var;
                if(var.size() == 0) break;
                nbv = nbv + 1;
                vs.push_back(var);
            }
            tr.setNew(vs);
            if(tr.getOld().size() != nbv) {
                aout("Cette instruction copier et son instruction exec\n");
                aout("ne sont pas en correspondance : fin de session.\n");
                pause();
                return 1;
            }
            listetrv.pop_back();
            listetrv.push_back(tr);
            // Pour copier les variables en arguments de ce fichier de commandes
            for(unsigned int i=0; i<nbv; i++) {
                bigRa x;
                if(chercherra(lect-1, tr.getOld()[i], x))
                    archiverra(lect, tr.getNew()[i], x);
                else {
                    aout("L'une des variables qu'il fallait copier\n");
                    aout("n'a pas été trouvée : fin de session.\n");
                    pause();
                    return 1;
                }
            }
            continue;
        }
        copier = false;
        // Pour effectuer l'intruction "exec" (exemple : exec a,b,c)
        if(keywd(line, ligne, "exec")) {
            char* chrs = new char[1+cmde.size()];
            unsigned int i;
            for(i=0; i<cmde.size(); i++) {
                if(cmde[i] != ',') chrs[i] = cmde[i];
                else chrs[i] = ' ';
            }
            chrs[i] = '\0';
            std::string cmdn = std::string(chrs);
            delete [] chrs;
            std::stringstream ss(cmdn);
            std::string exec, file;
            ss >> exec >> file;
            Trans tr(file);
            tr.setNiv(lect+1);
            std::vector<std::string> vs;
            for(;;) {
                std::string var;
                ss >> var;
                if(var.size() == 0) break;
                vs.push_back(var);
            }
            tr.setOld(vs);
            std::vector<unsigned int> vui;
            for(unsigned int i=0; i<vs.size(); i++) vui.push_back(0);
            tr.setIndic(vui);
            listetrv.push_back(tr);
            if(lect == 9) {
                std::cout << "Ce fichier de commandes est au niveau maximum de fonctionnement.\n";
                std::cout << "Opera ne peut pas en utiliser un autre. Fin de session.\n";
                pause();
                return 1;
            }
            filesin[lect+1].open(file.c_str());
            if(!filesin[lect+1].good()) {
                std::cout << "Le fichier " << file << " n'est pas disponible.\n";
                continue;
            }
            ret.clear();
            here = -1;
            copier = true;
            lect = lect + 1;
            // Pour créer last dans le fichier appelé
            archiverra(lect, "last", br0);
            continue;
        }
        // La commande "renvoyer var" met à jour dans le fichier appelant
        // la variable associée à la variable locale var du fichier appelé.
        if(keywd(line, ligne, "renvoyer")) {
            if(lect == 0) continue;
            std::string name = ligne.substr(8);
            if(name == "last" ) {
                aout("La variable last ne peut pas être renvoyée.\n");
                continue;
            }
            Trans tr = listetrv.back();
            int nbv = tr.getNew().size();
            std::string var;
            bool done = false;
            for(int i=0; i<nbv; i++)
                if(tr.getNew()[i] == name) {
                    bigRa val;
                    chercherra(lect, name, val);
                    modifierra(lect-1, tr.getOld()[i], val);
                    std::cout << tr.getOld()[i] << " = " << val << std::endl;
                    done = true;
                    break;
                }
            if(!done) std::cout << "Renvoyer " << name << " est impossible." << std::endl;
            continue;
        }
        // La commande "prochain res" permet de créer dans le fichier de commandes appelant 
        // une variable indicée ayant la valeur actuelle de last et le nom associé à l'argument res.
        // L'indice utilisé commence à 1 et il est incrémenté à chaque utilisation. 
        // Mais, si cette variable indicée existe déjà, l'indice utilisé commence ensuite.
        if(keywd(line, ligne, "prochain")) {
            if(lect == 0) continue;
            std::string name = ligne.substr(8);
            Trans tr = listetrv.back();
            int nbv = tr.getNew().size();
            std::vector<unsigned int> vui;
            bool done = false;
            for(int i=0; i<nbv; i++)
                if(tr.getNew()[i] == name) {
                    vui = tr.getIndic();
                    unsigned int ui = vui[i];
                    std::string var;
                    bigRa x;
                    // Si la variable souhaitée existe déjà
                    // on incrémente l'indice utilisable.
                    do{
                        ++ui;
                        std::stringstream sstr;
                        sstr << ui;
                        var = tr.getOld()[i] + "[" + sstr.str() + "]";
                    }while(chercherra(lect-1, var, x));
                    std::stringstream ststr;
                    ststr << ui;
                    var = tr.getOld()[i] + "[" + ststr.str() + "]";
                    chercherra(lect, "last", x);
                    archiverra(lect-1, var, x);
                    std::cout << var << " = " << x << std::endl;
                    vui[i] = ui;
                    tr.setIndic(vui);
                    // Mise à jour de listetrv
                    listetrv.pop_back();
                    listetrv.push_back(tr);
                    done = true;
                    break;
                }
            if(!done) std::cout << "Prochain " << name << " est impossible." << std::endl;
            continue;
        }
        // La commande "recevoir var don" permet de créer ou de modifier 
        // la variable locale var avec la valeur de la variable principale don
        if(keywd(line, ligne, "recevoir")) {
            if(lect == 0) continue;
            std::stringstream ss(cmde);
            std::string verbe, var, don;
            ss >> verbe >> var >> don;
            bigRa val;
            if(chercherra(0, don, val)) {
                bigRa x;
                if(chercherra(lect, var, x)) modifierra(lect, var, val);
                else archiverra(lect, var, val);
                std::cout << var << " = " << val << std::endl;
            }
            else {
                std::cout << "La variable principale " << don << " n'existe pas." << std::endl;
                std::cout << "Fin de session." << std::endl;
                pause();
                return 1;
            }
            continue;
        }
        // La commande "envoyer var res" permet de créer la variable principale res 
        // si elle n'existe pas encore avec la valeur de la variable locale var 
        // Si non on crée une nouvelle variable principale nommée var[2] ou var[3] ou etc. 
        if(keywd(line, ligne, "envoyer")) {
            if(lect == 0) continue;
            std::stringstream ss(cmde);
            std::string verbe, var, res;
            ss >> verbe >> var >> res;
            bigRa val;
            if(!chercherra(lect, var, val)) {
                std::cout << "La variable locale " << var << " n'existe pas." << std::endl;
                continue;
            }
            bigRa x;
            if(!chercherra(0, res, x)) {
                archiverra(0, res, val);
                std::cout << res << " = " << val << std::endl;
                continue;
            }
            else {
                int nb = 1;
                std::string nres;
                for(;;) {
                    nb = nb+1;
                    std::stringstream sstr;
                    sstr << nb;
                    nres = res + "[" + sstr.str() + "]";
                    if(chercherra(0, nres, x)) continue;
                    else break;
                }
                archiverra(0, nres, val);
                std::cout << nres << " = " << val << std::endl;
                continue;
            }
        }
        // Pour afficher l'aide
        if(instr(cmde, ligne, "aide")) {
            aide();
            continue;
        }
        // Pour faire une pause dans un fichier de commandes (faire : <enter>)
        if(instr(cmde, ligne, "pause")) {
            if(lect == 0) continue;
            int car = getchar();
            if(car == 0) continue; else continue;
        }
        // Pour afficher toutes les variables du niveau actuel (sauf last)
        if(instr(cmde, ligne, "lister")) {
            for(std::list<Var>::iterator it=listera.begin(); it!=listera.end(); ++it) {
                if((*it).getNiv() != lect) continue;
                if((*it).getNom() == "last") continue;
                std::string var = (*it).getNom();
                bigRa val = (*it).getRa();
                std::cout << var << " = " << val << std::endl;
            }
            continue;
        }
        // Pour noter toutes les variables du niveau actuel
        // Si le fichier filename existe déjà l'archivage est refusé.
        if(keywd(line, ligne, "noter")) {
            std::string filename = ligne.substr(5);
            std::ifstream filein(filename.c_str(), std::ifstream::in);
            if(filein.good()) {
                std::cout << "Le fichier " << filename << " existe : il faut un autre nom." << std::endl;
                filein.close();
                continue;
            }  
            std::ofstream fileout(filename.c_str(), std::ofstream::out);
            if(!fileout.good()) {
                aout("Le fichier d'archivage n'a pas pu être créé.\n");
                continue;
            }  
            for(std::list<Var>::iterator it=listera.begin(); it!=listera.end(); ++it)
                if((*it).getNiv() == lect) {
                    if((*it).getNom() == "last") continue;
                    std::string var = (*it).getNom();
                    bigRa val = (*it).getRa();
                    fileout << var << " = " << val << std::endl;
                }
            fileout.close();
            std::cout << "Le fichier " << filename << " est disponible." << std::endl;
            continue;
        }
        // Pour garder toutes les variables du niveau actuel
        // Si le fichier filename existe déjà : il est remplacé
        if(keywd(line, ligne, "garder")) {
            std::string filename = ligne.substr(6);
            bool newfile = true;
            std::ifstream filein(filename.c_str(), std::ifstream::in);
            if(filein.good()) {
                filein.close();
                newfile = false;
            }  
            std::ofstream fileout(filename.c_str(), std::ofstream::out);
            if(!fileout.good()) {
                aout("Le fichier désigné n'a pas pu être créé.\n");
                continue;
            }  
            for(std::list<Var>::iterator it=listera.begin(); it!=listera.end(); ++it)
                if((*it).getNiv() == lect) {
                    if((*it).getNom() == "last") continue;
                    std::string var = (*it).getNom();
                    bigRa val = (*it).getRa();
                    fileout << var << " = " << val << std::endl;
                }
            fileout.close();
            if(newfile) {
                std::cout << "Le fichier " << filename << " est disponible." << std::endl;
                continue;
            }
            else {
                std::cout << "Le fichier " << filename;
                aout(" est remplacé.\n");
                continue;
            }
        }
        // Pour créer ou mettre à jour au niveau actuel toutes les variables qui sont disponibles
        // dans un fichier obtenu précédemment avec la commande "noter" ou la commande "garder"
        if(keywd(line, ligne, "lire")) {
            std::string filename = ligne.substr(4);
            std::ifstream filein(filename.c_str(), std::ifstream::in);
            if(filein.good()) {
                bool done = false;
                while(!done) {
                    std::string instr;
                    std::getline(filein, instr);
                    if(!filein.good()) {done = true; break;}
                    std::size_t found = instr.find("=");
                    std::string var = instr.substr(0, found-1);
                    instr = instr.substr(found+2); 
                    bigRa v, x;
                    eval(instr, v);
                    if(chercherra(lect, var, x)) modifierra(lect, var, v);
                    else archiverra(lect, var, v);
                    std::cout << var << " = " << v << std::endl;
                }
                filein.close();
                continue;
            }
            std::cout << "Le fichier " << filename << " n'est pas disponible." << std::endl;
            continue;
        }
        // Pour afficher en format scientifique la valeur d'une variable ou d'une expression
        if(keywd(line, ligne, "valeur")) {
            std::string st = ligne.substr(6);
            bigRa x;
            bool good = eval(st, x);
            if(!good) {
                std::cout << "Variable ou expression invalide." << std::endl;
            }
            else {
                std::cout << std::setprecision(10) << ra2dbl(x) << std::endl;
                modifierra(lect, "last", x);
            }
            continue;
        }
        // Pour afficher le nombre de chiffres décimaux significatifs
        // de la partie entière d'une variable ou d'une expression
        if(keywd(line, ligne, "nbch")) {
            std::string st = ligne.substr(4);
            Integer n;
            bool good = nval(st, n);
            if(!good) {
                std::cout << "Variable ou expression invalide." << std::endl;
            }
            else if(n == 0) {
                std::cout << "0" << std::endl;
                bigRa br0;
                modifierra(lect, "last", br0);
            }
            else {
                std::stringstream ss;
                ss << n;
                int r = ss.str().size();
                if(n < 0) r = r-1;
                std::cout << r << std::endl;
                bigRa brr = bigRa(r);
                modifierra(lect, "last", brr);
            }
            continue;
        }
        // Pour calculer de la partie entière d'une variable ou d'une expression
        if(keywd(line, ligne, "enti")) {
            std::string st = ligne.substr(4);
            Integer n;
            bool good = nval(st, n);
            if(!good) {
                std::cout << "Variable ou expression invalide." << std::endl;
            }
            else if(n == 0) {
                std::cout << "0" << std::endl;
            }
            else {
                std::cout << n << std::endl;
                bigRa brn = bigRa(n);
                modifierra(lect, "last", brn);
            }
            continue;
        }
        // Pour calculer de la partie fractionaire d'une variable ou d'une expression
        if(keywd(line, ligne, "frac")) {
            std::string st = ligne.substr(4);
            Integer n;
            bool good = nval(st, n);
            if(!good) {
                std::cout << "Variable ou expression invalide." << std::endl;
            }
            else {
                bigRa x;
                eval(st, x);
                bigRa r = x - bigRa(n);
                std::cout << r << std::endl;
                modifierra(lect, "last", r);
            }
            continue;
        }
        // Pour calculer le numérateur d'une variable ou d'une expression
        if(keywd(line, ligne, "num")) {
            std::string st = ligne.substr(3);
            bigRa x;
            bool good = eval(st, x);
            if(!good) {
                std::cout << "Variable ou expression invalide." << std::endl;
            }
            else {
                bigRa n = x.getNum();
                std::cout << n << std::endl;
                modifierra(lect, "last", n);
            }
            continue;
        }
        // Pour calculer le dénominateur d'une variable ou d'une expression
        if(keywd(line, ligne, "den")) {
            std::string st = ligne.substr(3);
            bigRa x;
            bool good = eval(st, x);
            if(!good) {
                std::cout << "Variable ou expression invalide." << std::endl;
            }
            else {
                bigRa n = x.getDen();
                std::cout << n << std::endl;
                modifierra(lect, "last", n);
            }
            continue;
        }
        // Pour calculer le reste de deux variables ou expressions
        // ayant pour valeurs deux entiers
        if(keywd(line, ligne, "reste")) {
            std::string st = ligne.substr(5);
            std::size_t fv = st.find(",");
            if(fv == std::string::npos || fv==0 || fv==st.size()-1) {
                aout("reste n,d : instruction non reconnue.\n");
                continue;
            }
            std::string left = st.substr(0, fv);
            std::string right = st.substr(fv+1);
            bigRa r1, r2;
            if(!(eval(left, r1) && eval(right, r2))) {
                aout("reste n,d : instruction non reconnue.\n");
                continue;
            }
            if(!(isEnti(r1) && isEnti(r2))) {
                aout("Il faut deux entiers : instruction invalide.\n");
                continue;
            }
            Integer r = r1.getNum()/r2.getNum();
            r = r1.getNum() - r*r2.getNum();
            std::cout << r << std::endl;
            bigRa brr = bigRa(r);
            modifierra(lect, "last", brr);
            continue;
        }
        // Pour calculer le pgcd de deux variables ou expressions
        // ayant pour valeurs deux entiers
        if(keywd(line, ligne, "pgcd")) {
            std::string st = ligne.substr(4);
            std::size_t fv = st.find(",");
            if(fv == std::string::npos || fv==0 || fv==st.size()-1) {
                aout("pgcd a,b : instruction non reconnue.\n");
                continue;
            }
            std::string left = st.substr(0, fv);
            std::string right = st.substr(fv+1);
            bigRa r1, r2;
            if(!(eval(left, r1) && eval(right, r2))) {
                aout("pgcd a,b : instruction non reconnue.\n");
                continue;
            }
            if(!(isEnti(r1) && isEnti(r2))) {
                aout("Il faut deux entiers : instruction invalide.\n");
                continue;
            }
            Integer r = gcd(r1.getNum(), r2.getNum());
            std::cout << r << std::endl;
            bigRa brr = bigRa(r);
            modifierra(lect, "last", brr);
            continue;
        }
        // Pour calculer le ppcm de deux variables ou expressions
        // ayant pour valeurs deux entiers
        if(keywd(line, ligne, "ppcm")) {
            std::string st = ligne.substr(4);
            std::size_t fv = st.find(",");
            if(fv == std::string::npos || fv==0 || fv==st.size()-1) {
                aout("ppcm a,b : instruction non reconnue.\n");
                continue;
            }
            std::string left = st.substr(0, fv);
            std::string right = st.substr(fv+1);
            bigRa r1, r2;
            if(!(eval(left, r1) && eval(right, r2))) {
                aout("ppcm a,b : instruction non reconnue.\n");
                continue;
            }
            if(!(isEnti(r1) && isEnti(r2))) {
                aout("Il faut deux entiers : instruction invalide.\n");
                continue;
            }
            Integer i1, i2, n, d, r;
            i1 = r1.getNum();
            i2 = r2.getNum();
            d = gcd(i1, i2);
            if(d != 0) {
                n = i1*i2;
                if(n < 0) n = -n;
                r = n/d;
            }
            else r = 0;
            std::cout << r << std::endl;
            bigRa brr = bigRa(r);
            modifierra(lect, "last", brr);
            continue;
        }
        // Pour calculer un entier au hasard entre deux variables ou expressions
        // ayant pour valeurs deux entiers
        if(keywd(line, ligne, "hasard")) {
            std::string st = ligne.substr(6);
            std::size_t fv = st.find(",");
            if(fv == std::string::npos || fv==0 || fv==st.size()-1) {
                aout("hasard a,b : instruction non reconnue.\n");
                continue;
            }
            std::string left = st.substr(0, fv);
            std::string right = st.substr(fv+1);
            bigRa r1, r2;
            if(!(eval(left, r1) && eval(right, r2))) {
                aout("hasard a,b : instruction non reconnue.\n");
                continue;
            }
            if(!(isEnti(r1) && isEnti(r2))) {
                aout("Il faut deux entiers : instruction invalide.\n");
                continue;
            }
            Integer i1, i2;
            i1 = r1.getNum();
            i2 = r2.getNum();
            const int64_t rmx64 = static_cast<int64_t>(RAND_MAX);
            // (2^30-1)=(2^15-1)(2^15+1)=(2^15-1)((2^15-1)+2)
            const int64_t xrand_max = rmx64 * (rmx64 + 2);
            // r = i1 + (i2 - i1)*xrand()/xrand_max
            double x = double(i2 - i1)*double(xrand())/double(xrand_max);
            Integer r = i1 + entier(dbl2ra(x));
            std::cout << r << std::endl;
            bigRa brr = bigRa(r);
            modifierra(lect, "last", brr);
            continue;
        }
        // Pour calculer l'inverse modulaire r d'un entier a modulo un entier m
        // Il faut pgcd(a, m) = 1 si non : r = 0 et de plus : 0 < a < m
        if(keywd(line, ligne, "invmod")) {
            std::string st = ligne.substr(6);
            std::size_t fv = st.find(",");
            if(fv == std::string::npos || fv==0 || fv==st.size()-1) {
                aout("invmod a,m : instruction non reconnue.\n");
                continue;
            }
            std::string left = st.substr(0, fv);
            std::string right = st.substr(fv+1);
            bigRa r1, r2;
            if(!(eval(left, r1) && eval(right, r2))) {
                aout("invmod a,m : instruction non reconnue.\n");
                continue;
            }
            if(!(isEnti(r1) && isEnti(r2))) {
                aout("Il faut deux entiers : instruction invalide.\n");
                continue;
            }
            Integer a, m;
            a = r1.getNum();
            m = r2.getNum();
            if(a <= 0 || a >= m) {
                aout("Pour invmod a,m : il faut 0 < a < m\n");
                continue;
            }
            Integer r = invMod(a, m);
            std::cout << r << std::endl;
            bigRa brr = bigRa(r);
            modifierra(lect, "last", brr);
            continue;
        }
        // Pour calculer l'exponentiation modulaire : x^e mod(m)
        if(keywd(line, ligne, "expmod")) {
            std::string st = ligne.substr(6);
            std::size_t fv = st.find(",");
            if(fv == std::string::npos || fv==0 || fv==st.size()-1) {
                aout("expmod x,e,m : instruction non reconnue.\n");
                continue;
            }
            std::string left = st.substr(0, fv);
            bigRa r1;
            if(!(eval(left, r1))) {
                aout("expmod x,e,m : instruction non reconnue.\n");
                continue;
            }
            if(!(isEnti(r1))) {
                aout("Il faut trois entiers : instruction invalide.\n");
                continue;
            }
            st = st.substr(fv+1);
            fv = st.find(",");
            if(fv == std::string::npos || fv==0 || fv==st.size()-1) {
                aout("expmod x,e,m : instruction non reconnue.\n");
                continue;
            }
			left = st.substr(0, fv);
            std::string right = st.substr(fv+1);
            bigRa r2, r3;
            if(!(eval(left, r2) && eval(right, r3))) {
                aout("expmod x,e,m : instruction non reconnue.\n");
                continue;
            }
            if(!(isEnti(r2) && isEnti(r3))) {
                aout("Il faut trois entiers : instruction invalide.\n");
                continue;
            }
            Integer x, e, m;
            x = r1.getNum();
            e = r2.getNum();
            m = r3.getNum();
            if(x < 0 || e < 0 || m < 0) {
                aout("expmod x,e,m : les entiers négatifs sont invalides\n");
                continue;
            }
            if(!(x < m)) {
                aout("expmod x,e,m : il faut x < m\n");
                continue;
            }
            Integer r = expMod(x, e, m);
            std::cout << r << std::endl;
            bigRa brr = bigRa(r);
            modifierra(lect, "last", brr);
            continue;
        }        
        // Pour calculer le premier nombre premier suivant un entier
        // ou une expression ayant pour valeur un entier
        if(keywd(line, ligne, "pnps")) {
            std::string st = ligne.substr(4);
            bigRa x;
            if(!eval(st, x)) {
                aout("pnps n : instruction non reconnue.\n");
                continue;
            }
            if(!isEnti(x)) {
                aout("Il faut un entier : instruction invalide.\n");
                continue;
            }
            Integer n = x.getNum();
            if(n < 0) {
                aout("Il faut un entier positif ou nul.\n");
                continue;
            }
            Integer r = n + 1;
			while(!isprime(r)) {r = r + 1;}
            std::cout << r << std::endl;
            bigRa brr = bigRa(r);
            modifierra(lect, "last", brr);
            continue;
        }
        // Pour calculer un facteur premier d'une variable ou d'une expression
        // ayant pour valeur un entier
        if(keywd(line, ligne, "facteur")) {
            std::string st = ligne.substr(7);
            bigRa x;
            if(!eval(st, x)) {
                aout("facteur n : instruction non reconnue.\n");
                continue;
            }
            if(!isEnti(x)) {
                aout("Il faut un entier : instruction invalide.\n");
                continue;
            }
            Integer r = x.getNum();
            if(r < 0) r = -r;
            if(!isprime(r)) r = get_factor(r);
            if(r == 0) aout("Algorithme rho en échec.\n");
            else std::cout << r << std::endl;
            bigRa brr = bigRa(r);
            modifierra(lect, "last", brr);
            continue;
        }
        // Pour calculer la primalité d'une variable ou d'une expression
        // ayant pour valeur un entier
        if(keywd(line, ligne, "prem")) {
            std::string st = ligne.substr(4);
            bigRa x;
            if(!eval(st, x)) {
                aout("prem n : instruction non reconnue.\n");
                continue;
            }
            if(!isEnti(x)) {
                aout("Il faut un entier : instruction invalide.\n");
                continue;
            }
            Integer n = x.getNum();
            int r = 1;
            if(!isprime(n)) r = 0;
            std::cout << r << std::endl;
            bigRa brr = bigRa(r);
            modifierra(lect, "last", brr);
            continue;
        }
        // Pour continuer si last est positif ou si non abandonner
        if(instr(cmde, ligne, "continuer")) {
            if(lect == 0) continue;
            bigRa x; 
            chercherra(lect, "last", x);
            if(cmpRa(x, br0) > 0) continue;
            else {
                filesin[lect].close();
                fermeture();
                continue;
            }
        }
        // Pour quitter si last est positif ou si non continuer
        if(instr(cmde, ligne, "quitter")) {
            if(lect == 0) continue;
            bigRa x;
            chercherra(lect, "last", x);
            if(cmpRa(x, br0) > 0) { 
                filesin[lect].close();
                fermeture();
                continue;
            }
            else continue;
        }
        // Exemple : si expr
        // Pour sauter une instruction si expr est nulle ou négative
        if(keywd(line, ligne, "si")) {
            if(lect == 0) continue;
            std::string st = ligne.substr(2);
            bigRa x;
            if(!eval(st, x)) {
                aout("si expr : instruction non reconnue.\n");
                continue;
            }
            if(cmpRa(x, br0) > 0) continue;
            else {jump = true; continue;}
        }
        // Pour effectuer l'instruction : "boucle"
        if(instr(cmde, ligne, "boucle")) {
            if(lect == 0) continue;
            // si cette boucle n'est pas encore déjà notée : on la note
            if((ret.size() == 0) || (ret.size() != 0 && ret[ret.size()-1] != back)) {
                if(back == -1) { // si l'instruction précédente n'existe pas
                    aout("Instruction boucle invalide : fin de session.\n");
                    pause();
                    return 1;
                }
                ret.push_back(back);
            }
            // si l'instruction précédente est une condition positive : on continue
            bigRa x;
            chercherra(lect, "last", x);
            if(cmpRa(x, br0) > 0) continue;
            // si non : on efface la note et on va après son retour correspondant
            else {
                ret.pop_back();
                int nret = 1;
                do {
                    std::getline(filesin[lect], ligne);
                    outspaces(ligne);
                    delcom(ligne);
                    if(!filesin[lect].good()) {
                        aout("Le retour est absent : fin de session.\n");
                        pause();
                        return 1;
                    }
                    if(ligne == "boucle") nret = nret + 1;
                    if(ligne == "retour") nret = nret - 1;
                }while(!(ligne == "retour" && nret == 0));
                continue;
            }
        }
        // Pour effectuer l'instruction : "retour"
        if(instr(cmde, ligne, "retour")) {
            if(lect == 0) continue;
            if(ret.size() == 0) {
                aout("Instruction retour invalide : fin de session.\n");
                pause();
                return 1;
            }
            filesin[lect].seekg(ret.back());
            continue;
        }
        // Pour supprimer une variable du niveau actuel
        if(keywd(line, ligne, "supprimer")) {
            std::string var = ligne.substr(9);
            if(var == "last" ) {
                aout("La variable last ne peut pas être supprimée.\n");
                continue;
            }
            if(supprimerra(lect, var)) {
                std::cout << var;
                aout(" est supprimé.\n");
            }
            else std::cout << "Variable inconnue." << std::endl;
            continue;
        }
        // Pour terminer cette session
        if(instr(cmde, ligne, "exit")) break;
        // Pour évaluer une expression arithmétique
        std::size_t found = ligne.find("=");
        if(found == std::string::npos) {
            if(ligne.size() == 0) continue;
            bigRa v;
            if(eval(ligne, v)) {
                std::cout << v << std::endl;
                modifierra(lect, "last", v);
                continue;
            }
            else {
                std::string setapprox ("setapprox");
				if(ligne.compare(setapprox) == 0) {
                    std::cout << approxim(0) << std::endl;
                    continue;
                }
                std::cout << "Variable ou expression invalide." << std::endl;
                continue;
            }
        }
        else {
            std::string res = ligne.substr(0, found);
            ligne = ligne.substr(found+1);
            if(res.size() == 0 || ligne.size() == 0) {
                aout("Instruction invalide.\n");
                aide();
                continue;
            }
            if(!isname(res)) {
                aout("Variable invalide.\n");
                continue;
            }
            if(res == "last" ) {
                aout("La variable last n'est modifiable que par un résultat qui la précède.\n");
                continue;
            }
            if(res == "setapprox") {
                setapprox(ligne);
                continue;
            }
            bigRa v;
            if(!eval(ligne, v)) {
                std::cout << "Expression invalide." << std::endl;
                continue;
            }
            bigRa x;
            if(chercherra(lect, res, x)) modifierra(lect, res, v);
            else archiverra(lect, res, v);
            std::cout << res << " = " << v << std::endl;
            modifierra(lect, "last", v);
            continue;
        }
    }
    return 0;
}

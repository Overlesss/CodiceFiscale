#include "nascita.h"
#include <fstream>
#include <algorithm>

Nascita::Nascita() : luogo(""), belfiore("") {} //richiamati implicitamente costruttori di default per i sottooggetti

Nascita::Nascita(const std::string& b) : luogo(""), belfiore(b) {}

Nascita::Nascita(const Data& d) : Data(d), luogo(""), belfiore("") {}

Nascita::Nascita(const Data& d, std::string l, std::string b) : Data(d), luogo(l), belfiore (b) {}

Nascita::Nascita(const Nascita& n) : Data(n), luogo(n.luogo), belfiore(n.belfiore) {}

std::istream& operator>>(std::istream& is, Nascita& n) throw(CFexception) {
    //costruzione luogo (possibili input con spazi):
    std::string luogoNascita, comune, provincia;
    std::cout<<"Inserire stato di nascita: ";
    std::cin.ignore();
    std::getline(is, luogoNascita);
    if(luogoNascita == "") throw FineFileLuogo();
    std::transform(luogoNascita.begin(), luogoNascita.end(), luogoNascita.begin(), ::toupper);
    if(luogoNascita == "ITALIA") {
        std::cout<<"Inserire comune di nascita: ";
        std::getline(is, comune);
        std::transform(comune.begin(), comune.end(), comune.begin(), ::toupper);
        std::cout<<"Inserire sigla provincia: ";
        std::getline(is, provincia);
        std::transform(provincia.begin(), provincia.end(), provincia.begin(), ::toupper);
        luogoNascita = comune + " (" + provincia + ")";
    }
    n.luogo = luogoNascita;
    return is;
}

void Nascita::apriFile(std::vector<Nascita>& vec_luoghi) throw(CFexception) {
    std::ifstream in_luoghi;
    in_luoghi.open("belfiore.txt"); //file contenente nell'ordine: codice belfiore, luogo (Stato per estero, comune con sigla provincia tra parentesi per italia); (campi separati da tabulazioni)

    //apertura file
    if(in_luoghi.is_open()) {

        //per ogni riga del file, la sottostringa prima della tabulazione viene salvata nel campo dati belfiore, cio' che segue nel campo dati luogo
        while(!in_luoghi.eof()) {
            std::string temp;
            std::getline(in_luoghi, temp);
            std::string separatore = "\t";
            Nascita x;
            size_t inizio = 0;
            size_t lung = temp.find(separatore);
            x.belfiore = temp.substr(inizio, lung);
            inizio = lung + 1;
            lung = (temp.size()) - inizio -1;
            x.luogo = temp.substr(inizio, lung);
            vec_luoghi.push_back(x);
        }
    } else throw ErrFile();
    in_luoghi.close();
}


void Nascita::creaDaCodice (const std::string& cod) throw(CFexception) {
    Data::creaDaCodice(cod.substr(0,5)); //puo' lanciare eccezione ErrMese
    Data::controllo(); //puo' lanciare eccezione ErrData
    belfiore = cod.substr(5);
    controllo(); //puo' lanciare eccezioni: ErrFile, ErrBelfiore
    //in controllo viene assegnato campo luogo, se trovata corrispondenza
}


std::string Nascita::generaCodice() const throw() {
    //in controllo che segue input dei dati, viene assegnato campo belfiore, se trovata corrispondenza
    return belfiore;
}


void Nascita::controllo() throw(CFexception) {
    std::vector<Nascita> vec_luoghi;

    //apertura file belfiore.txt ed estrazione dati in vec_luoghi
    apriFile(vec_luoghi); //puo' lanciare eccezione ErrFile

    bool trovato = false;
    if(luogo != "") {
        //ricerca campo dati luogo in vec_luoghi
        for(std::vector<Nascita>::const_iterator it = vec_luoghi.begin() ; it != vec_luoghi.end() && !trovato; ++it)
            //se si trova corrispondenza, si estrae codice belfiore corrispondente
            if((it->luogo).compare(luogo) == 0) {
                belfiore = it->belfiore;
                trovato = true;
            }
    } else {
        //ricerca campo dati belfiore in vec_luoghi
        for(std::vector<Nascita>::const_iterator it = vec_luoghi.begin() ; it != vec_luoghi.end() && !trovato; ++it)
            //se si trova corrispondenza, si estrae luogo corrispondente
            if((it->belfiore).compare(belfiore) ==0) {
                luogo = it->luogo;
                trovato = true;
            }
    }
    //se campo dati (luogo o belfiore) non trovato, non si puo' continuare con la generazione del codice fiscale
    if(!trovato) {
        if(luogo != "") throw ErrLuogo();
        else throw ErrBelfiore();
    }
}

std::vector<std::string> Nascita::getStati() {
    std::vector<Nascita> vec_luoghi;
    std::vector<std::string> vec_stati;

    vec_stati.push_back("ITALIA");

    //apertura file belfiore.txt ed estrazione dati in vec_luoghi
    try { apriFile(vec_luoghi); } catch(ErrFile) { throw ErrFile(); }

    //ricerca campo dati luogo in vec_luoghi
    bool trovato = false;
    for(std::vector<Nascita>::const_iterator it = vec_luoghi.begin() ; it != vec_luoghi.end() && !trovato; ++it) {
        if((it->belfiore).substr(0, 1).compare("Z") == 0) {
            vec_stati.push_back(it->luogo);
        }
    }

    std::sort(vec_stati.begin(), vec_stati.end());

    return vec_stati;
}


std::string Nascita::toString() const throw() {
    std::string nascitaS = " data di nascita: " + Data::toString() + "\n";
    nascitaS += " luogo di nascita: " + luogo;
    return nascitaS;
}


Nascita::operator bool() const throw() {
    Data dataEstratta; //costruttore di default inizializza campi a 0
    const Data* pD = dynamic_cast<const Data*>(this);
    if(pD) dataEstratta = *pD;
    return (luogo != "") && (dataEstratta);
}

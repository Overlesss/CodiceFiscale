#include "data.h"
#include <limits>

const std::string Data::CODICI_MESI ("ABCDEHLMPRST");


Data::Data(unsigned int a, unsigned int m, unsigned int g) : anno(a), mese (m), giorno(g) {}


Data::Data(const Data& d) {
    anno = d.anno;
    mese = d.mese;
    giorno = d.giorno;
}


unsigned int Data::estraiGiorno() const throw() {
    return giorno;
}


std::istream& operator>>(std::istream& is, Data& d) throw(CFexception){
    const std::string CIFRE("0123456789");
    std::string::size_type pos;
    char c;
    std::cout<<"Inserire data di nascita nel formato gg-mm-aa: ";

    //lettura giorno
    if(!(is >> c)) throw FineFileData();
    pos = CIFRE.find(c);
    if(pos == std::string::npos) { is.ignore(std::numeric_limits<char>::max(),'\n'); throw ErrSintData(); } //ignorati tutti i caratteri digitati per data
    d.giorno = pos;
    if(!(is >> c)) throw FineFileData();
    if(c != '-') {
        pos = CIFRE.find(c);
        if(pos == std::string::npos) { is.ignore(std::numeric_limits<char>::max(),'\n'); throw ErrSintData(); }
        d.giorno = d.giorno * 10 + pos;
        if(!(is >> c)) throw FineFileData();
        if(c != '-') { is.ignore(std::numeric_limits<char>::max(),'\n'); throw ErrSintData(); }

    }

    //lettura mese
    if(!(is >> c)) throw FineFileData();
    pos = CIFRE.find(c);
    if(pos == std::string::npos) { is.ignore(std::numeric_limits<char>::max(),'\n'); throw ErrSintData(); }
    d.mese = pos;
    if(!(is >> c)) throw FineFileData();
    if(c != '-') {
        pos = CIFRE.find(c);
        if(pos == std::string::npos) { is.ignore(std::numeric_limits<char>::max(),'\n'); throw ErrSintData(); }
        d.mese = d.mese * 10 + pos;
        if(!(is >> c)) throw FineFileData();
        if(c != '-') { is.ignore(std::numeric_limits<char>::max(),'\n'); throw ErrSintData(); }

    }

    //lettura anno
    if(!(is >> c)) throw FineFileData();
    pos = CIFRE.find(c);
    if(pos == std::string::npos) { is.ignore(std::numeric_limits<char>::max(),'\n'); throw ErrSintData(); }
    d.anno = pos;
    is >> c;
    if(is  && CIFRE.find(c) != std::string::npos) {
        pos = CIFRE.find(c);
        d.anno = d.anno * 10 + pos;
    } else if(is) { is.ignore(std::numeric_limits<char>::max(),'\n'); throw ErrSintData(); }

    return is;
}


void Data::creaDaCodice (const std::string& cod) throw(CFexception) {

    //creazione anno
    anno = stringToUInt(cod.substr(0,2));

    //creazione mese
    unsigned int m = 0;
    bool trovato = false;
    //cerca corrispondenza di c con caratteri in CODICI_MESI
    for(std::string::const_iterator it = CODICI_MESI.begin(); !trovato && it != CODICI_MESI.end(); ++it) {
        m += 1;
        if(*it == cod.at(2)) trovato = true;
    }
    //se trovato, il codice mese estratto dal codice fiscale e' valido
    if(trovato) mese = m;
    else throw ErrMese();

    //creazione giorno
    giorno = stringToUInt(cod.substr(3,2));
    if(giorno>31) giorno -= 40;
}


std::string Data::generaCodice() const throw() {
    std::string cod = "";

    //generazione codice anno
    //se anno <9, si concatena uno zero
    unsigned int ultimeCifre = anno % 100;
    if(ultimeCifre <= 9) cod = "0" + Data::uintToString(ultimeCifre);
    else cod = Data::uintToString(ultimeCifre);

    //generazionne codice corrispondente a mese
    cod += CODICI_MESI[mese-1];

    //generazione codice giorno
    //se giorno <9, si concatena uno zero
    if(giorno <= 9) cod += "0" + Data::uintToString(giorno);
    else cod += Data::uintToString(giorno);

    return cod;
}


void Data::controllo() throw(CFexception) {
    const unsigned int MAX_GIORNI_MESI[] = {31,29,31,30,31,30,31,31,30,31,30,31};
    if((mese < 1 || mese > 12) || (giorno < 1 || giorno > 31)) throw ErrData();
    unsigned int g_max = MAX_GIORNI_MESI[mese-1];
    //giorno non deve essere maggiore del massimo dei giorni per il mese estratto
    if(g_max < giorno) throw ErrData();
    //controllo giorni anni bisestili
    if(mese == 2 && giorno > 28) {
        if(!(((anno%4 == 0)&&(anno%100 != 0)) || (anno%400 == 0))) throw ErrData();
    }
}


std::string Data::toString() const throw() {
    std::string g = Data::uintToString(giorno);
    std::string m = Data::uintToString(mese);
    std::string a = Data::uintToString(anno);
    //se anno/mese/giorno < 9, concateno uno 0
    if(giorno < 10) g = "0" + g;
    if(mese < 10) m = "0" + m;
    if(anno < 10) a = "0" + a;
    std::string dataS = g + "/" + m + "/" + "19" + a;
    //i nati tra 1900-1918 hanno le stesse 2 cifre relative all'anno dei nati tra 2000-2018
    if(anno < 18) dataS += " oppure " + g + "/" + m + "/" + "20" + a;
    return dataS;
}


Data::operator bool() const throw() {
    //se oggetto Data ha valori assegnati (diversi da parametri di default) allora giorno != 0 (per controllo validita' data)
    return giorno != 0;
}

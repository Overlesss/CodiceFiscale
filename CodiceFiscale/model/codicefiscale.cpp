#include "codicefiscale.h"
#include <algorithm>

const std::string CodiceFiscale::ALFABETO("ABCDEFGHIJKLMNOPQRSTUVWXYZ");


CodiceFiscale::CodiceFiscale(const std::string& s) : codice(s) {}


CodiceFiscale::CodiceFiscale(const CodiceFiscale& x) {
    codice = x.codice;
}


unsigned int CodiceFiscale::cinDispari(const std::string& dispari) throw() {
    //da controllo, codice contiene solo cifre oppure lettere dell'alfabeto
    //dispari e' una sottostringa di codice

    const std::string ALFABETO_DISPARI("BAKPLCQDREVOSFTGUHMINJWZYX");
    unsigned int sum = 0; //conterra' la somma dei valori assegnati ai caratteri di dispari
    const int NUMERI[] = {1, 0, 5, 7, 9, 13, 15, 17, 19, 21};
    for(std::string::const_iterator it = dispari.begin(); it < dispari.end(); ++it)
        if(ALFABETO.find(*it) != std::string::npos)
            //il carattere di dispari in posizione it e' una lettera dell'alfabeto
            sum += ALFABETO_DISPARI.find(*it);
        else {
            //il carattere di dispari in posizione it e' una cifra
            unsigned int n = (*it) - '0';  //conversione char->unsigned int
            sum += NUMERI [n];
        }
    return sum;
}


unsigned int CodiceFiscale::cinPari(const std::string& pari) throw() {
    //da controllo, codice contiene solo cifre oppure lettere dell'alfabeto
    //pari e' una sottostringa di codice

    unsigned int sum = 0; //conterra' la somma dei corrispondenti valori dei caratteri di pari
    for(std::string::const_iterator it = pari.begin(); it < pari.end(); ++it)
        if(ALFABETO.find(*it) != std::string::npos)
            //il carattere di pari in posizione it e' una lettera dell'alfabeto
            sum += ALFABETO.find(*it);
        else {
            //il carattere di pari in posizione it e' una cifra
            unsigned int n = (*it) - '0';  //conversione char->unsigned int
            sum += n;
        }
    return sum;
}


std::string CodiceFiscale::estraiCodIdentificativo() const throw() { return codice.substr(0,6); }

std::string CodiceFiscale::estraiCodAnno() const throw() { return codice.substr(6,2); }

std::string CodiceFiscale::estraiCodMese() const throw() { return codice.substr(8,1); }

std::string CodiceFiscale::estraiCodGiornoSesso() const throw() { return codice.substr(9,2); }

std::string CodiceFiscale::estraiCodLuogo() const throw() { return codice.substr(11,4); }

std::string CodiceFiscale::estraiCin() const throw() { return codice.substr(15); }


bool CodiceFiscale::controlloCin(const std::string& cin_atteso) const throw(CFexception) {
    //codice e' composto da 16 caratteri, il carattere in ultima posizione e' il CIN
    //controllo corrispondenza CIN del codice fiscale rispetto al parametro passato alla funzione
    const std::string cin_attuale = codice.substr(15);
    if(cin_attuale.compare(cin_atteso) != 0) throw ErrCf();
    return true;
}


std::string CodiceFiscale::estraiCodice () const throw() {
    return codice;
}


std::istream& operator>>(std::istream& is, CodiceFiscale& x) throw(CFexception) {
    std::cout<<"Inserire il codice fiscale: ";
    std::string str;

    is.ignore(); //scarta carattere newline nel buffer di input (dalla precedente digitazione della funzione)
    std::getline(is, str); //stop quando raggiunge carattere newline (newline letto e scartato)
    if(is.gcount() == 0) throw FineFileCf();

    //conversione minuscole in maiuscole
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    x.codice=str;
    x.controllo(); //controllo lunghezza e formato potenzialmente corretto, puo' lanciare eccezioni: ErrCf, CfLungo, CfCorto
    return is;
}


void CodiceFiscale::creaDaCodice(const std::string& x) throw() {
    if(codice != x) codice = x;
}


std::string CodiceFiscale::generaCodice() const throw() {
    std::string cf_estratto = codice;
    //se codice ha 16 caratteri, elimino ultimo carattere per calcolare CIN
    if(cf_estratto.length() == 16)
        cf_estratto.erase(cf_estratto.begin()+15);

    //calcolo CIN sulla base dei primi 15 caratteri di cod_fiscale
    std::string pari;
    std::string dispari;
    for(unsigned int i = 0; i < cf_estratto.length(); ++i) {
        if(i % 2 == 0) dispari.push_back(cf_estratto[i]);
        else pari.push_back(cf_estratto[i]);
    }
    unsigned int i = (cinPari(pari) + cinDispari(dispari)) % 26;

    //si ritorna una stringa composta dal CIN calcolato
    std::string cin (1,ALFABETO[i]); //costruttore std::string(size_t n, char c)
    return cin;
}


void CodiceFiscale::controllo() throw(CFexception) {
    const std::string CIFRE("0123456789");

    //controllo lunghezza codice
    std::string::size_type lunghezza = codice.length();
    if(lunghezza<16) throw CfCorto();
    else if(lunghezza>16) throw CfLungo();

    //codice ha 16 caratteri
    //devono essere così costituiti: [a-z]{6}[0-9]{2}[a-z][0-9]{2}[a-z][0-9]{3}[a-z]

    std::string::size_type pos;

    //controllo posizione identificativo:
    std::string temp = (*this).CodiceFiscale::estraiCodIdentificativo();
    std::string::const_iterator inizio = temp.begin();
    std::string::const_iterator fine = temp.end();
    for(std::string::const_iterator it=inizio; it!=fine; ++it) {
        pos = ALFABETO.find(*it);
        if(pos == std::string::npos) throw ErrCf();
    }

    //controllo posizione anno:
    temp = (*this).CodiceFiscale::estraiCodAnno();
    inizio = temp.begin();
    fine = temp.end();
    for(std::string::const_iterator it=inizio; it!=fine; ++it) {
        pos = CIFRE.find(*it);
        if(pos == std::string::npos) throw ErrCf();
    }

    //controllo posizione mese:
    temp = (*this).CodiceFiscale::estraiCodMese();
    pos = ALFABETO.find(temp);
    if(pos == std::string::npos) throw ErrCf();

    //controllo giorno-sesso
    temp = (*this).CodiceFiscale::estraiCodGiornoSesso();
    inizio = temp.begin();
    fine = temp.end();
    for(std::string::const_iterator it=inizio; it!=fine; ++it) {
        pos = CIFRE.find(*it);
        if(pos == std::string::npos) throw ErrCf();
    }

    //controllo posizione luogo:
    temp = (*this).CodiceFiscale::estraiCodLuogo();
    inizio = temp.begin();
    fine = temp.end();
    pos = ALFABETO.find(*inizio);
    if(pos == std::string::npos) throw ErrCf();
    for(std::string::const_iterator it=inizio+1; it!=fine; ++it) {
        pos = CIFRE.find(*it);
        if(pos == std::string::npos) throw ErrCf();
    }

    //controllo posizione carattere di controllo:
    temp = (*this).CodiceFiscale::estraiCin();
    pos = ALFABETO.find(temp);
    if(pos == std::string::npos) throw ErrCf();
}


std::string CodiceFiscale::toString() const throw() {
    return codice;
}


CodiceFiscale::operator bool() const throw() {
    return codice != "";
}

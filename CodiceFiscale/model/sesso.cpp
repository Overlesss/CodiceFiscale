#include "sesso.h"
#include <limits>

Sesso::Sesso() : genere('0') {}


Sesso::Sesso(const Sesso& x) {
    genere = x.genere;
}


char Sesso::estraiGenere() const throw() {
    return genere;
}

Sesso& Sesso::operator=(const char& x) {
    if(genere != x) genere=x;
    return *this;
}

std::istream& operator>>(std::istream& is, Sesso& s) throw(CFexception) {
    char c;
    std::cout<<"Inserire sesso (digitare m oppure f): ";
    if(!(is >> c)) throw FineFileSesso();
    s.genere = c;
    return is;
}


void Sesso::creaDaCodice (const std::string& cod) throw() {
    //validita' data (e quindi sesso) controllata nei precedenti controlli su Data

    //estrazione codice giorno da codice fiscale (sulla base del quale e' calcolato il sesso)
    int n = stringToUInt(cod);
    if(n>0 && n<=31) genere = 'M';
        else genere = 'F'; //da metodo Nascita::creaDaCodice, l'altro intervallo è necessariamente n>40&&n<=71
}


std::string Sesso::generaCodice() const throw() {
    //valori possibili per genere: f/F/m/M
    if(genere == 'f' || genere == 'F') return "40";
    else return "0";
}


void Sesso::controllo() throw(CFexception) {
    if(genere!='m' && genere!='f' && genere!='M' && genere!='F') throw ErrSesso();
}


std::string Sesso::toString() const throw() {
    //valori possibili per genere: f/F/m/M
    if(genere == 'M' || genere == 'm') return "MASCHIO";
    else return "FEMMMINA";
}


Sesso::operator bool() const throw() {
    return genere != '0';
}

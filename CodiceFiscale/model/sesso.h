#ifndef SESSO_H
#define SESSO_H

#include "datipersona.h"
#include<iostream>

class Sesso : public DatiPersona {
private:
    char genere;

public:
    Sesso(); //costruttore di default
    Sesso(const Sesso&); //costruttore di copia
    Sesso& operator=(const char&);

    char estraiGenere() const throw(); //estrazione campo dati genere
    friend std::istream& operator>>(std::istream&, Sesso&) throw(CFexception);

    virtual void creaDaCodice(const std::string&) throw(); //creazione campo dati genere dalla corrispondente sottostringa del codice fiscale
    virtual std::string generaCodice() const throw(); //genera caratteri relativi al sesso, ovvero la cifra da sommare al giorno di nascita
    virtual void controllo() throw(CFexception); //controllo validita' genere
    virtual std::string toString() const throw(); //ritorna stringa corrispondente al genere
    virtual operator bool() const throw(); //ritorna true se oggetto Sesso ha campo dati assegnato (diverso da parametri di default)
};

#endif // SESSO_H

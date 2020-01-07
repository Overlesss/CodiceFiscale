#ifndef DATA_H
#define DATA_H

#include "datipersona.h"
#include <iostream>


class Data : public DatiPersona {
private:
    unsigned int anno;
    unsigned int mese;
    unsigned int giorno;

    //campo dati statico di utilita':
    static const std::string CODICI_MESI;

public:
    Data(unsigned int =0, unsigned int =0, unsigned int =0); //costruttore a 3 parametri
    Data(const Data&); //costruttore di copia

    unsigned int estraiGiorno() const throw(); //estrazione campo dati giorno
    friend std::istream& operator>>(std::istream&, Data&) throw(CFexception);

    virtual void creaDaCodice(const std::string&) throw(CFexception); //creazione campi oggetto Data dalla corrispondente sottostringa del codice fiscale
    virtual std::string generaCodice() const throw(); //genera caratteri corrispondenti alla data di nascita per il codice fiscale
    virtual void controllo() throw(CFexception); //controllo validita' oggetto Data
    virtual std::string toString() const throw(); //ritorna stringa corrispondente a oggetto Data
    virtual operator bool() const throw(); //ritorna true se oggetto Data ha valori assegnati (diversi da parametri di default)
};

#endif // DATA_H

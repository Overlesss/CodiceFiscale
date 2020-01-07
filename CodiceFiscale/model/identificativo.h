#ifndef INDENTIFICATIVO_H
#define INDENTIFICATIVO_H

#include "sesso.h"


class Identificativo : public Sesso {
private:
    std::string nome;
    std::string cognome;

    //campo dati statico di utilita':
    static const std::string VOCALI;

    //funzioni implementative non facenti parte dell'interfaccia pubblica:
    static unsigned int contaConsonanti(std::string) throw(); //restituisce il numero di consonanti in una stringa
	std::string generaCodCognome() const throw(); //genera 3 caratteri del cognome per il codice fiscale
    std::string generaCodNome() const throw(); //genera 3 caratteri del nome per il codice fiscale
    
public:
    Identificativo(); //costruttore di default
    Identificativo(std::string, std::string); //costruttore a 2 parametri
    Identificativo(const Identificativo&); //costruttore di copia

    friend std::istream& operator>>(std::istream&, Identificativo&) throw(CFexception);

    virtual void creaDaCodice(const std::string&) throw(); //creazione sigla nome e cognome dalla corrispondente sottostringa del codice fiscale
    virtual std::string generaCodice() const throw(); //genera caratteri corrispondenti a cognome e nome per il codice fiscale
    virtual void controllo() throw(CFexception); //controllo legalita' oggetto Identificativo
    virtual std::string toString() const throw(); //ritorna stringa corrispondente a nome e cognome
    virtual operator bool() const throw(); //ritorna true se cognome e nome hanno valori assegnati
};

#endif // INDENTIFICATIVO_H

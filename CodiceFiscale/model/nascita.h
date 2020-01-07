#ifndef NASCITA_H
#define NASCITA_H

#include "data.h"
#include <vector>

class Nascita : public Data {
private:
    std::string luogo;
    std::string belfiore;

    //funzione implementativa non facente parte dell'interfaccia pubblica:
    static void apriFile(std::vector<Nascita> &) throw(CFexception); //apre file belfiore.txt ed estrae dati in un vector<Nascita>

public:
    Nascita(); //costruttore di default
    Nascita(const std::string&); //costruttore ad un parametro
    Nascita(const Data&); //costruttore ad un parametro di tipo Data
    Nascita(const Data&, std::string, std::string =""); //costruttore a due/tre parametri
    Nascita(const Nascita&); //costruttore di copia

    friend std::istream& operator>>(std::istream&,Nascita&) throw(CFexception);
    static std::vector<std::string> getStati(); // restituisce un vettore degli stati

    virtual void creaDaCodice (const std::string&) throw(CFexception); //creazione dati relativi alla nascita dalla corrispondente sottostringa del codice fiscale
    virtual std::string generaCodice() const throw(); //genera caratteri corrispondenti a luogo per il codice fiscale (codice belfiore)
    virtual std::string toString() const throw(); //ritorna stringa corrispondente a oggetto Nascita (e relativi sottooggetti)
    virtual void controllo() throw(CFexception); //controlla validita' luogo e assegna belfiore corrispondente, o viceversa
    virtual operator bool() const throw(); //ritorna true se oggetto Nascita e relativi sottooggetti hanno valori assegnati (diversi da valori di default)
};

#endif // NASCITA_H

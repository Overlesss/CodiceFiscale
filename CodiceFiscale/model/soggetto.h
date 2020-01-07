#ifndef PERSONA_H
#define PERSONA_H

#include "datipersona.h"
#include "nascita.h"
#include "identificativo.h"
#include "codicefiscale.h"


//classe che rappresenta un soggetto tramite i suoi dati
class Soggetto {
private:
    CodiceFiscale cf;
    Identificativo nominativo;
    Sesso sesso;
    Nascita datiNascita;

public:
    Soggetto(); //costruttore di default
    Soggetto(Nascita, Sesso, Identificativo);
    Soggetto(const CodiceFiscale&); //costruttore ad un parametro (di tipo CodiceFiscale)
    Soggetto(const Soggetto&); //costruttore di copia

    void assegna(DatiPersona *) throw(); //assegna valori ai campi dati
    DatiPersona* creaDaCodice(DatiPersona*, const std::string&) throw(CFexception); //creazione oggetto del tipo passato come parametro da relativa sottostringa del codice fiscale
    static std::string generaCodice(DatiPersona*) throw(CFexception); //generazione parte di codice fiscale da dato (passato come parametro) che caratterizza un soggetto
    static void controllo(DatiPersona*) throw(CFexception); //controllo validita' dato (passato come parametro) che caratterizza un soggetto
    static std::string estraiDati(const DatiPersona*); //stampa dato (passato come parametro) che caratterizzano un Soggetto
    std::string getDati() const;
    friend std::ostream& operator<<(std::ostream&, const Soggetto&) throw(); //stampa dati Soggetto
};

#endif // PERSONA_H

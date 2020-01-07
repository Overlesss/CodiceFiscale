#ifndef CODICEFISCALE_H
#define CODICEFISCALE_H

#include "datipersona.h"
#include <iostream>


class CodiceFiscale : public DatiPersona {
private:
    std::string codice;

    //campo dati statico di utilita':
    static const std::string ALFABETO;

    //funzioni implementative non facenti parte dell'interfaccia pubblica:
    static unsigned int cinDispari(const std::string &) throw(); //ritorna la somma dei valori assegnati ai caratteri di posizione dispari in codice
    static unsigned int cinPari(const std::string &) throw(); //ritorna la somma dei valori assegnati ai caratteri di posizione pari in codice

public:
    CodiceFiscale(const std::string& =""); //costruttore ad 1 parametro con argomento di default
    CodiceFiscale(const CodiceFiscale&); //costruttore di copia

    std::string estraiCodIdentificativo() const throw(); //estrae posizioni 0-5 che identificano l'identificativo
    std::string estraiCodAnno() const throw(); //estrae posizioni 6-7 che identificano anno
    std::string estraiCodMese() const throw(); //estrae posizione 8 che identifica mese
    std::string estraiCodGiornoSesso() const throw(); //estrae posizioni 9-10 che identificano giorno e sesso
    std::string estraiCodLuogo() const throw(); //estrae posizioni 11-14 che identificano luogo
    std::string estraiCin() const throw(); //estrae posizione 15 che identifica carattere di controllo

    bool controlloCin(const std::string&) const throw(CFexception); //controllo corrispondenza cin del codice fiscale con cin passato a funzione
    std::string estraiCodice() const throw(); //estrazione campo dati codice
    friend std::istream& operator>>(std::istream&, CodiceFiscale&) throw(CFexception);

    virtual void creaDaCodice(const std::string&) throw(); //crea codice fiscale da stringa passata come parametro
    virtual std::string generaCodice() const throw(); //genera il carattere corrispondente al codice di controllo CIN
    virtual void controllo() throw(CFexception); //controllo lunghezza cf e corretta posizione caratteri/cifre
    virtual std::string toString() const throw(); //ritorna stringa corrispondete a codice fiscale
    virtual operator bool() const throw(); //ritorna true se codice fiscale ha un valore assegnato
};

#endif // CODICEFISCALE_H

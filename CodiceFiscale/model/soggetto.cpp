#include "soggetto.h"

Soggetto::Soggetto() {}

Soggetto::Soggetto(Nascita n, Sesso s, Identificativo a)
    : nominativo(a), sesso(s), datiNascita(n)  {}

Soggetto::Soggetto(const CodiceFiscale& c) : cf(c) {}


Soggetto::Soggetto(const Soggetto &s) : cf(s.cf), nominativo(s.nominativo), sesso(s.sesso), datiNascita(s.datiNascita) {}


void Soggetto::assegna(DatiPersona* pDP) throw() {
    Sesso* pS = dynamic_cast<Sesso*>(pDP);
    if(pS) {
        Identificativo* pI = dynamic_cast<Identificativo*>(pDP);
        if(pI) nominativo = *pI;
        else sesso = *pS;
        return;
    }
    Nascita* pN = dynamic_cast<Nascita*>(pDP);
    if(pN) {
        datiNascita = *pN;
        return;
    }
    CodiceFiscale* pCf = dynamic_cast<CodiceFiscale*>(pDP);
    if(pCf) {
        cf = *pCf;
        return;
    }
}


DatiPersona* Soggetto::creaDaCodice(DatiPersona* pDP, const std::string& cod) throw(CFexception) {
    pDP->creaDaCodice(cod);
    Nascita* pN = dynamic_cast<Nascita*>(pDP);
    if(pN) {
        datiNascita = *pN;
        return &datiNascita;
    }
    Sesso* pS = dynamic_cast<Sesso*>(pDP);
    if(pS) {
        sesso = *pS;
        return &sesso;
    }
    return 0;
}


std::string Soggetto::generaCodice(DatiPersona* pDP) throw(CFexception) {
    Nascita* pN = dynamic_cast<Nascita*>(pDP);
    if(pN)
        return (pN->Data::generaCodice() + pN->generaCodice());
    return pDP->generaCodice();
}


void Soggetto::controllo(DatiPersona* pDP) throw(CFexception) {
    pDP->controllo();
}


std::string Soggetto::estraiDati(const DatiPersona* pDP) {
    return pDP->toString();
}

std::string Soggetto::getDati() const {
    std::string os;
    if(cf) { os="Codice fiscale: "+Soggetto::estraiDati(&cf); }
    os+="\n";
    if(nominativo) { os+="Nome e cognome: "+Soggetto::estraiDati(&nominativo); }
    os+="\n";
    if(sesso) { os+="Sesso: "+Soggetto::estraiDati(&sesso); }
    os+="\n";
    if(datiNascita) { os+=Soggetto::estraiDati(&datiNascita)+"\n"; }
    return os;
}


std::ostream& operator<<(std::ostream& os, const Soggetto& s) throw() {
    if(s.cf) { os<<" codice fiscale: "<<Soggetto::estraiDati(&s.cf)<<"\n"; }
    if(s.nominativo) { os<<" nome e cognome: "<<Soggetto::estraiDati(&s.nominativo)<<"\n"; }
    if(s.sesso) { os<<" sesso: "<<Soggetto::estraiDati(&s.sesso)<<"\n"; }
    if(s.datiNascita) { os<<Soggetto::estraiDati(&s.datiNascita)<<"\n"; }
    return os;
}


#include "identificativo.h"
#include <algorithm>


const std::string Identificativo::VOCALI("AEIOU");


Identificativo::Identificativo() : Sesso(), nome(""), cognome("") {}


Identificativo::Identificativo(std::string n, std::string c) : Sesso(), nome(n), cognome(c) {}


Identificativo::Identificativo(const Identificativo& a) : Sesso(a), nome(a.nome), cognome(a.cognome) {}


unsigned int Identificativo::contaConsonanti(std::string str) throw() {
    unsigned int c = 0; //c contiene il numero di consonanti trovate in str
    std::string::const_iterator it = str.begin();
    while(it < str.end()) {
        if(std::find(VOCALI.begin(), VOCALI.end(), *it) == VOCALI.end()) ++c;
        ++it;
    }
    return c;
}


std::string Identificativo::generaCodCognome() const throw() {
    //cognome contiene almeno 2 caratteri (da metodo controllo)
    std::string str; //conterra' codice cognome

    if(cognome.size() < 3) {
        //cognome ha meno di 3 caratteri, si aggiunge X alla fine

        //estrazione delle consonanti seguite dalle vocali, se presenti, nel loro ordine
        std::string::size_type pos = VOCALI.find(*(cognome.begin()));
        if(pos != std::string::npos) { //il primo carattere del cognome e' una vocale
            //controllo del secondo carattere
            pos = VOCALI.find(*(cognome.end()-1));
            if(pos == std::string::npos) { //il secondo carattere e' una consonante, str deve contenere prima la consonante, poi la vocale
                str.push_back(*(cognome.end()-1));
                str.push_back(*(cognome.begin()));
            } else str = cognome; //sono due vocali, str le contiene nel loro ordine
        } else str = cognome; //sono due consonanti, str le contiene nel loro ordine

        str.push_back('X'); //aggiunta X come terzo char
    } else {
        //cognome piu' lungo di 3 caratteri

        //costruzione cognome con le consonanti
        std::string::const_iterator it = cognome.begin();
        while(it < cognome.end() && str.size() < 3) {
            if(std::find(VOCALI.begin(), VOCALI.end(), *it) == VOCALI.end()) str.push_back(*it); // se e' una consonante viene inserita in str
            ++it;
        }

        //caso in cui le consonanti sono < 2
        it = cognome.begin();
        while(str.size() < 3){
            if(std::find(VOCALI.begin(), VOCALI.end(), *it) != VOCALI.end())
                str.push_back(*it);
            ++it;
        }
    }
    return str;
}


std::string Identificativo::generaCodNome() const throw() {
    //nome contiene almeno 2 caratteri (da metodo controllo)
    std::string str; //conterra' codice nome

    //controllo lunghezza nome
    if(nome.size() < 3) {
        //cognome ha meno di 3 caratteri, va aggiunta X alla fine

        //estrazione delle consonanti seguite dalle vocali, se presenti, nel loro ordine
        std::string::size_type pos = VOCALI.find(*(nome.begin()));
        if(pos != std::string::npos) { //il primo carattere del nome e' una vocale
            //controllo del secondo carattere
            pos = VOCALI.find(*(nome.end()-1));
            if(pos == std::string::npos) { //il secondo carattere e' una consonante, str deve contenere prima la consonante, poi la vocale
                str.push_back(*(nome.end()-1));
                str.push_back(*(nome.begin()));
            } else str = nome; //sono due VOCALI, str le contiene nel loro ordine
        } else str = nome; //sono due consonanti, str le contiene nel loro ordine

        str.push_back('X'); //aggiunta X come terzo char
    } else {
        //nome piu' lungo di 3 caratteri
        unsigned int cons = contaConsonanti(nome);
        unsigned int aux = 0;
        std::string::const_iterator it = nome.begin();

        //numero consonanti >3, si estraggono da nome la 1a, 3a e 4a
        while(it < nome.end() && str.size() < 3) {
            if(cons > 3) {
                if(std::find(VOCALI.begin(), VOCALI.end(), *it) == VOCALI.end()) {
                    if(aux != 1) str.push_back(*it);
                    ++aux;
                }
            } else {
                //numero consonanti <=3, si estraggono le consonanti di nome nel loro ordine
                if(std::find(VOCALI.begin(), VOCALI.end(), *it) == VOCALI.end()) str.push_back(*it);
            }
            ++it;
        }

        // caso in cui le consonanti sono < 2
        it = nome.begin();
        while(str.size() < 3){
            if(std::find(VOCALI.begin(), VOCALI.end(), *it) != VOCALI.end())
                str.push_back(*it);
            ++it;
        }
    }
    return str;
}

std::istream& operator>>(std::istream& is, Identificativo& i) throw(CFexception) {
    //possibili input contenenti spazi
    std::string nome, cognome;
    std::cout<<"Inserisci cognome: ";
    std::cin.ignore(); //scarta carattere newline nel buffer di input (dalla precedente digitazione della funzione)
    std::getline(is, cognome); //stop quando raggiunge carattere newline (newline letto e scartato)
    if(is.gcount() == 0) throw AntrCorto();
    std::cout<<"Inserisci nome: ";
    std::getline(is, nome);
    if(is.gcount() == 0) throw AntrCorto();
    nome.erase(remove_if(nome.begin(), nome.end(), isspace), nome.end()); //eliminazione spazi nome
    cognome.erase(remove_if(cognome.begin(), cognome.end(), isspace), cognome.end()); //eliminazione spazi cognome
    std::transform(nome.begin(), nome.end(), nome.begin(), ::toupper); //conversione minuscole in maiuscole
    std::transform(cognome.begin(), cognome.end(), cognome.begin(), ::toupper); //conversione minuscole in maiuscole
    i.nome = nome;
    i.cognome = cognome;
    return is;
}

void Identificativo::creaDaCodice(const std::string& cod) throw() {
    //cognome e nome conterranno il corrispondente codice estratto dal cf
    cognome = cod.substr(0,3);
    nome = cod.substr(3,3);
}


std::string Identificativo::generaCodice() const throw() {
    return generaCodCognome() + generaCodNome();
}


void Identificativo::controllo() throw(CFexception) {
    const std::string ALFABETO("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    //nome e cognome devono essere composti da almeno 2 caratteri
    if(nome.size() < 2 || cognome.size() < 2) throw AntrCorto();

    //controllo caratteri nome e cognome (le stringhe non contengono spazi)
    //nome e cognome possono contenere solo lettere dell'alfabeto
    std::string::size_type pos;
    for(std::string::const_iterator it = nome.begin(); it != nome.end(); ++it) {
        pos = ALFABETO.find(*it);
        if(pos == std::string::npos) throw ErrAntr();
    }
    for(std::string::const_iterator it = cognome.begin(); it != cognome.end(); ++it) {
        pos = ALFABETO.find(*it);
        if(pos == std::string::npos) throw ErrAntr();
    }
}


std::string Identificativo::toString() const throw() {
    return (cognome + " " + nome);
}


Identificativo::operator bool() const throw() {
    //controllo se oggetto identificativo ha valori assegnati (diversi da parametri di default)
    return cognome != "";
}

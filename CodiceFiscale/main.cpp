#include "model/datipersona.h"
#include "model/soggetto.h"

#include <QApplication>
#include "view/mainwindow.h"

void sceltaFunzione(int&,bool&) throw(CFexception); //scelta funzionalita' da eseguire
void nuovaOperazione(bool&) throw(CFexception); //scelta se eseguire nuova operazione o terminare programma
void eseguiFunzione(const int&); //esecuzione funzione scelta in funzione sceltaFunzione


int main(int argc, char* argv[]) {
    /*int fun=-1;
    bool continua=true;

    //continua con diverse funzionalita' del programma fino al comando di uscita
    while(continua) {

        //scelta funzione da eseguire
        sceltaFunzione(fun,continua);
        if(continua) {

            //esecuzione funzione
            eseguiFunzione(fun);
            fun=-1;

            //richiesta se continuare o terminare
            nuovaOperazione(continua);
        }
    }
    std::cout<<"Programma terminato."<<std::endl;*/
    QApplication app(argc, argv);
    MainWindow widget;
    widget.show();

    return app.exec();
}

void sceltaFunzione (int& fun, bool& continua) throw(CFexception) try {
    std::cout<<"Scegliere un'operazione:"<<std::endl;
    std::cout<<"(1) Calcolo codice fiscale,"<<std::endl;
    std::cout<<"(2) Verifica validita' codice fiscale,"<<std::endl;
    std::cout<<"(3) Estrazione dati codice fiscale,"<<std::endl;
    std::cout<<"(4) Calcolo parti codice fiscale,"<<std::endl;
    std::cout<<"(0) Per uscire dal programma."<<std::endl;
    std::cout<<"Digitare il numero della funzione desiderata: ";

    //scelta funzione
    char f;
    std::string::size_type pos;
    std::string cifre_fun("01234");
    std::cin>>f;

    //controllo validita' input
    pos=cifre_fun.std::string::find(f);
    if(pos==std::string::npos) throw SceltaErrata();
    fun=pos;
    if(fun==0) continua=false;
}
catch(CFexception& e) { std::cerr<<e.estraiErrore()<<std::endl; sceltaFunzione(fun,continua); } //input non corretto, richiesta se continuare o terminare


void eseguiFunzione(const int& fun) {
    //fun contiene: 1-calcolo cf, 2-verifica validita' cf, 3-estrazione dati cf
    switch(fun) {

        //1: calcolo cf
        case 1: {
            Soggetto s;
            Identificativo nominativo;
            Sesso sex;
            Nascita datiNascita;
            std::cout<<"\nDigitare caratteri senza accenti."<<std::endl;

            try {
                try{
                    std::cin>>nominativo; //puo' lanciare eccezione FineFileAntr
                    Soggetto::controllo(&nominativo); //puo' lanciare eccezioni: AntrCorto, ErrAntr
                }
                catch(ErrAntr &e) { std::cout<<e.estraiErrore()<<std::endl; throw CFexception("Funzione terminata."); }
                s.assegna(&nominativo);

                //costruzione sesso
                try {
                    std::cin>>sex; //puo' lanciare eccezioni: ErrSesso, FineFileSesso
                    Soggetto::controllo(&sex); //puo' lanciare eccezione ErrSesso
                }
                catch(ErrSesso &e) { std::cout<<e.estraiErrore()<<std::endl; throw CFexception("Funzione terminata."); }
                s.assegna(&sex);

                //costruzione data:
                Data dataNascita;
                try {
                    std::cin>>dataNascita; //puo' lanciare eccezioni: FineFileData, ErrSintData, ErrData
                    Soggetto::controllo(&dataNascita); //puo' lanciare eccezione ErrData
                }
                catch(ErrData &e) { std::cout<<e.estraiErrore()<<std::endl; throw CFexception("Funzione terminata."); }

                datiNascita = Nascita(dataNascita);
                try {
                    std::cin>>datiNascita;
                    Soggetto::controllo(&datiNascita); //puo' lanciare eccezioni: ErrLuogo, ErrFile
                }
                catch(ErrLuogo &e) { std::cout<<e.estraiErrore()<<std::endl; throw CFexception("Funzione terminata."); }
                catch(ErrFile &e) { std::cout<<e.estraiErrore()<<std::endl; throw CFexception("Funzione terminata."); }
                s.assegna(&datiNascita);
            }
            catch(CFexception& e) { std::cerr<<e.estraiErrore()<<std::endl; break; }

                //calcolo cf corrispondente a dati presi in input
                CodiceFiscale cfGenerato;
                std::string cod = Soggetto::generaCodice(&nominativo) + Soggetto::generaCodice(&datiNascita);

                //se persona di sesso femminile, a codice giorno va sommato 40
                std::string codS = Soggetto::generaCodice(&sex);
                if(codS != "0") {
                    unsigned int g = datiNascita.estraiGiorno();
                    g = g + DatiPersona::stringToUInt(codS);
                    cod.replace(9,2,DatiPersona::uintToString(g));
                }
                CodiceFiscale cfTemp = cod; //cfTemp composto da 15 caratteri
                cod.append(Soggetto::generaCodice(&cfTemp));
                cfGenerato.creaDaCodice(cod);

                s.assegna(&cfGenerato);
                std::cout<<std::endl<<"Il codice fiscale e': "<<Soggetto::estraiDati(&cfGenerato)<<std::endl;
        }
            break;

        //2: verifica validita' - 3: verifica validita' + estrazione dati
        case 2: case 3: {
            CodiceFiscale cf;
            Nascita datiNascita;
            Sesso sesso;
            try {
                //in input codice fiscale, controllo lunghezza e corretta posizione caratteri/cifre
                try { std::cin>>cf; } //puo' lanciare eccezioni: CfCorto, CfLungo, ErrCf, FineFileCf
                catch(ErrCf& e) { std::cerr<<e.estraiErrore()<<std::endl; throw CFexception("Funzione terminata."); }

                //creazione soggetto da cf
                Soggetto anonimo = cf;
                std::string codNascita = cf.estraiCodAnno() + cf.estraiCodMese() + cf.estraiCodGiornoSesso() + cf.estraiCodLuogo();
                try {
                    datiNascita = *(dynamic_cast<Nascita*>(anonimo.creaDaCodice(&datiNascita,codNascita))); //puo' lanciare eccezioni: ErrMese, ErrData,
                }
                //qualunque errore rilevato nei valori creati, e' un errore di sintassi del codice fiscale
                catch(CFexception &e) { throw ErrCf(); }

                std::string codGiornoSesso = cf.estraiCodGiornoSesso();
                sesso = *(dynamic_cast<Sesso*>(anonimo.creaDaCodice(&sesso,codGiornoSesso)));

                //calcolo cin atteso dai primi 15 caratteri del cf preso in input
                //controllo corrispondenza cin atteso con cin estratto da cf, se non corrisponde cf e' non valido
                const std::string cin_atteso = Soggetto::generaCodice(&cf);
                cf.controlloCin(cin_atteso);
                if(fun == 2)
                    //fun==2, si richiede solo verifica del codice fiscale
                    std::cout<<std::endl<<"Codice fiscale valido."<<std::endl;
                else {
                    //fun==3, si richiede stampa dei dati estratti dal codice fiscale
                    std::cout<<std::endl<<"Dati soggetto estratti da"<<anonimo<<std::endl;
                }
            }
            catch(CFexception& e) { std::cerr<<e.estraiErrore()<<std::endl; }
            }
            break;

        //4: calcolo parti cf
        case 4: {
            std::cout<<"Si vuole calcolare sottostringa del codice fiscale per:"<<std::endl;
            std::cout<<"(a) nome e cognome"<<std::endl;
            std::cout<<"(b) data di nascita"<<std::endl;
            std::cout<<"(c) luogo di nascita"<<std::endl;
            std::cout<<"(z) uscita"<<std::endl;

            //scelta funzione
            char c;
            bool ok = false;
            while(!ok) {
                std::cout<<"Digitare il carattere corrispondente alla scelta desiderata: ";
                std::string::size_type pos;
                std::string char_scelta("abcz");
                std::cin>>c;

                //controllo validita' input
                pos = char_scelta.std::string::find(c);
                if(pos != std::string::npos) ok = true;
                else std::cout<<"Numero inserito non corretto."<<std::endl;
            }
            if(c == 'z') break;

            //c contiene valore valido
            std::string codParziale;

            try {
                if(c == 'a') { //scelta identificativo
                    std::cout<<"\nDigitare caratteri senza accenti."<<std::endl;
                    Identificativo nominativo;
                    try {
                        std::cin>>nominativo; //puo' lanciare eccezione FineFileAntr
                        Soggetto::controllo(&nominativo); //puo' lanciare eccezioni: AntrCorto, ErrAntr
                        codParziale = Soggetto::generaCodice(&nominativo);
                        std::cout<<"Sottostringa del codice fiscale generata: "<<codParziale<<std::endl;
                    }
                    catch(ErrAntr& e) { std::cout<<e.estraiErrore()<<std::endl; throw CFexception("Funzione terminata."); }
                } else

                    if(c == 'b') { //scelta data
                        Data dataNascita; Sesso sex;
                        //costruzione data
                        try {
                            std::cin>>dataNascita; //puo' lanciare eccezioni: FineFileData, ErrSintData, ErrData
                            Soggetto::controllo(&dataNascita); //puo' lanciare eccezione ErrData
                        }
                        catch(FineFileData &e) { std::cout<<e.estraiErrore()<<std::endl; throw CFexception("Funzione terminata."); }
                        catch(ErrData &e) { std::cout<<e.estraiErrore()<<std::endl; throw CFexception("Funzione terminata."); }
                        //costruzione sesso
                        try {
                            std::cin>>sex; //puo' lanciare eccezioni: ErrSesso, FineFileSesso
                            Soggetto::controllo(&sex); //puo' lanciare eccezione ErrSesso
                        }
                        catch(ErrSesso &e) { std::cout<<e.estraiErrore()<<std::endl; throw CFexception("Funzione terminata."); }

                        codParziale = Soggetto::generaCodice(&dataNascita);
                        //se persona di sesso femminile, a codice giorno va sommato 40
                        std::string codS = Soggetto::generaCodice(&sex);
                        if(codS != "0") {
                            unsigned int g = dataNascita.estraiGiorno();
                            g = g + DatiPersona::stringToUInt(codS);
                            codParziale.replace(3,2,DatiPersona::uintToString(g));
                        }
                        std::cout<<"Sottostringa del codice fiscale generata: "<<codParziale<<std::endl;
                    } else

                        if(c == 'c') { //scelta luogo nascita
                            std::cout<<"\nDigitare caratteri senza accenti."<<std::endl;
                            Nascita luogoNascita;
                            try {
                                std::cin>>luogoNascita; //puo' lanciare eccezione FineFileLuogo
                                Soggetto::controllo(&luogoNascita); //puo' lanciare eccezioni: ErrLuogo, ErrFile
                                std::cout<<"Sottostringa del codice fiscale generata: "<<luogoNascita.generaCodice()<<std::endl;
                            }
                            catch(ErrLuogo &e) { std::cout<<e.estraiErrore()<<std::endl; throw CFexception("Funzione terminata."); }
                            catch(ErrFile &e) { std::cout<<e.estraiErrore()<<std::endl; throw CFexception("Funzione terminata."); }
                        }
            }
            catch(CFexception& e) {std::cout<<e.estraiErrore()<<std::endl; }
            break;
        }
    }
}

void nuovaOperazione(bool& continua) throw (CFexception) try {

    //scelta se continuare o terminare
    std::cout<<"Eseguire una nuova operazione? S/N: ";
    char n;

    //controllo validita' input
    std::string::size_type pos;
    std::string scelta_ok("SsNn");
    std::cin>>n;
    pos=scelta_ok.std::string::find(n);
    if(pos == std::string::npos) throw SceltaErrata();
    n = pos;
    if(n==2 || n==3) continua=false;
}
catch(CFexception &e) { std::cerr<<e.estraiErrore()<<std::endl; nuovaOperazione(continua); } //input non corretto, rilanciata funzione nuovaOperazione

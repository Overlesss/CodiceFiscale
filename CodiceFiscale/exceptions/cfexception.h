#ifndef CFEXCEPTION_H
#define CFEXCEPTION_H

#include <string>


class CFexception {
private:
    std::string err;
public:
    CFexception(const std::string& mess) : err(mess){}
    std::string estraiErrore() { return err; }
};


class SceltaErrata : public CFexception {
    public:
    SceltaErrata(const std::string& mess ="Input non corretto.") : CFexception(mess) {}
};


class ErrCf : public CFexception{
    public:
    ErrCf(const std::string& mess ="Codice fiscale non valido.") : CFexception(mess) {}
};


class FineFileCf: public ErrCf {
    public:
    FineFileCf(const std::string& mess ="Errore in input codice fiscale, EOF.") : ErrCf(mess) {}
};


class CfCorto : public ErrCf {
    public:
    CfCorto(const std::string& mess ="Codice fiscale troppo corto.") : ErrCf(mess) {}
};


class CfLungo : public ErrCf {
    public:
    CfLungo(const std::string& mess ="Codice fiscale troppo lungo.") : ErrCf(mess) {}
};


class ErrData : public CFexception {
    public:
    ErrData(const std::string& mess ="Data non corretta.") : CFexception(mess) {}
};


class ErrSintData : public ErrData {
    public:
    ErrSintData(const std::string& mess ="Errore in input data, formato non conforme.") : ErrData(mess) {}
};


class ErrMese: public ErrData {
    public:
    ErrMese(const std::string& mess ="Mese non corretto.") : ErrData(mess) {}
};


class FineFileData: public ErrData {
    public:
    FineFileData(const std::string& mess ="Errore in input data, EOF.") : ErrData(mess) {}
};


class ErrAntr : public CFexception {
    public:
    ErrAntr(const std::string& mess ="Nome e/o cognome non validi.") : CFexception(mess) {}
};


class AntrCorto: public ErrAntr {
    public:
    AntrCorto(const std::string& mess ="Nome e/o cognome troppo corti.") : ErrAntr(mess) {}
};


class ErrFile: public CFexception {
    public:
    ErrFile(const std::string& mess ="Errore nell'apertura del file belfiore.txt.") : CFexception(mess) {}
};


class ErrLuogo : public CFexception {
    public:
    ErrLuogo(const std::string& mess ="Luogo non corretto.") : CFexception(mess) {}
};


class ErrBelfiore : public ErrLuogo {
    public:
    ErrBelfiore(const std::string& mess ="Codice belfiore non corretto.") : ErrLuogo(mess) {}
};


class FineFileLuogo: public ErrLuogo {
    public:
    FineFileLuogo(const std::string& mess ="Errore in input luogo, EOF.") : ErrLuogo(mess) {}
};


class ErrSesso: public CFexception {
    public:
    ErrSesso(const std::string& mess ="Sesso non corretto.") : CFexception(mess) {}
};


class FineFileSesso: public ErrSesso {
    public:
    FineFileSesso(const std::string& mess ="Errore in input sesso, EOF.") : ErrSesso(mess) {}
};

#endif // CFEXCEPTION_H

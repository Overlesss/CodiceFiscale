#ifndef DATIPERSONA_H
#define DATIPERSONA_H

#include "exceptions/cfexception.h"
#include <string>


class DatiPersona { //classe base astratta
public:
    static std::string uintToString(unsigned int) throw(); //da unsigned int a string
    static unsigned int stringToUInt (const std::string&) throw(); //da string a unsigned int
    virtual ~DatiPersona() {}

    //funzioni virtuali pure
    virtual void creaDaCodice(const std::string&) =0;
    virtual std::string generaCodice() const throw() =0;
    virtual void controllo() =0;
    virtual std::string toString() const throw() =0;
    virtual operator bool() const throw() =0;
};

#endif // DATIPERSONA_H

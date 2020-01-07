#include "datipersona.h"
#include <sstream>

std::string DatiPersona::uintToString(unsigned int val) throw() {
    std::stringstream stream;
    stream << val;
    return stream.str();
}

unsigned int DatiPersona::stringToUInt (const std::string& s) throw() {
    std::stringstream ss(s);
    unsigned int val;
    return ss >> val ? val : 0;
}


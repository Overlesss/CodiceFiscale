#include "eccezioni.h"

Vuoto::Vuoto() {}

Vuoto::Vuoto(char c, QTextEdit*& out) {
    if(c == 'c') out->setText("Cognome vuoto.");
    if(c == 'n') out->setText("Nome vuoto.");
    if(c == 's') out->setText("Stato vuoto.");
    if(c == 'o') out->setText("Comune vuoto.");
    if(c == 'p') out->setText("Provincia vuoto.");
}

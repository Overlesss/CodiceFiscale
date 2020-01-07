#ifndef CALCOLOTAB_H
#define CALCOLOTAB_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QDateEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QClipboard>
#include <QGuiApplication>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QXmlStreamWriter>

#include "kalkabstract.h"
#include "./model/datipersona.h"
#include "./model/soggetto.h"
#include <string>

class CalcoloTabWidget : public KalkAbstract {
    Q_OBJECT

private:
    QLineEdit* cognomeEdit;
    QLineEdit* nomeEdit;
    QLineEdit* statoEdit;
    QLineEdit* provEdit;
    QLineEdit* comuneEdit;
    QRadioButton* maschio;
    QRadioButton* femmina;
    QDateEdit* dataEdit;
    QTextEdit* out;
    QComboBox* menu;
    QPushButton* copy;
    QPushButton* save;
    QPushButton* clear;
    QFile file;
    QTextStream fout;
public slots:
    void onTextChanged(const QString &); // slot che sblocca comuneEdit e provEdit se statoEdit è "italia"
    void calcola() throw(Vuoto); // slot che calcola il codice fiscale
    void pulisci(); // slot che resetta il form
    void copia(); // copia il codice fiscale negli appunti
    void salva(); // salva i dati nel file data.txt
    void pulisciFile(); // pulisce il file data.txt
    void nascondiBottoni(QString); // nasconde i bottoni di salva e copia quando il form viene modificato
public:
    CalcoloTabWidget();
    ~CalcoloTabWidget();
};

#endif // CALCOLOTAB_H

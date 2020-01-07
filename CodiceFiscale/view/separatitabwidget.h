#ifndef SEPARATIWIDGET_H
#define SEPARATIWIDGET_H

#include <string>
#include "./model/datipersona.h"
#include "./model/soggetto.h"
#include "kalkabstract.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QRadioButton>
#include <QComboBox>
#include <QSplitter>
#include <QPainter>

class SeparatiTabWidget : public KalkAbstract {
    Q_OBJECT

private:
    QLineEdit* cognomeEdit;
    QLineEdit* nomeEdit;
    QLineEdit* outIden;
    QDateEdit* dataEdit;
    QRadioButton* maschio;
    QRadioButton* femmina;
    QLineEdit* outData;
    QComboBox* menu;
    QLineEdit* statoEdit;
    QLineEdit* provEdit;
    QLineEdit* comuneEdit;
    QLineEdit* outLuogo;
public slots:
    void calcolaIden(); // calcola il codice relativo al nome e cognome
    void calcolaData(); // calcola il codice relativo alla data + sesso
    void calcolaLuogo(); // calcola il codice relativo al luogo
    void pulisciIden(); // pulisce l'output e l'input del nome e cognome
    void pulisciData(); // pulisce l'output della data + sesso e imposta l'input a valori di default
    void pulisciLuogo(); // pulisce l'output e l'input del luogo e mette "ITALIA" come default sullo stato
    void onTextChanged(const QString &); // slot che sblocca comuneEdit e provEdit se statoEdit è "italia"
    void calcola(); // calcola tutto ciò che è compilato
    void pulisci(); // pulisce tutti gli input e output
public:
    SeparatiTabWidget();
};

#endif // SEPARATIWIDGET_H

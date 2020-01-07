#ifndef INVERSOTAB_H
#define INVERSOTAB_H

#include "./model/soggetto.h"
#include "kalkabstract.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QTextStream>
#include <QFile>

class InversoTabWidget : public KalkAbstract {
    Q_OBJECT

private:
    QLineEdit* invEdit;
    QTextEdit* out;
public slots:
    void calcola() throw (CfCorto); // slot che restituisce le informazioni
    void pulisci(); // pulisce l'output e l'input
public:
    InversoTabWidget();
    bool contiene(QFile *, const QString);
    void stampa(QFile *, const QString);
    ~InversoTabWidget();
};

#endif // INVERSOTAB_H

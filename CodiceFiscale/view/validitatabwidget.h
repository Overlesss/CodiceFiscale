#ifndef VALIDITATAB_H
#define VALIDITATAB_H

#include "./model/soggetto.h"
#include "kalkabstract.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTextEdit>


class ValiditaTabWidget : public KalkAbstract {
    Q_OBJECT

private:
    QLineEdit* valEdit;
    QTextEdit* out;
public slots:
    void calcola() throw (CfCorto); // slot che controlla se è valido il cf
    void pulisci(); // pulisce output e form di input
public:
    ValiditaTabWidget();
    ~ValiditaTabWidget();
};

#endif // VALIDITATAB_H

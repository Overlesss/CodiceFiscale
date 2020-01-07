#ifndef KALKABSTRACT_H
#define KALKABSTRACT_H

#include <QWidget>
#include "./exceptions/eccezioni.h"

class KalkAbstract : public QWidget {
    Q_OBJECT
public slots:
    virtual void calcola() = 0;
    virtual void pulisci() = 0;
public:
    KalkAbstract(QWidget* parent = 0);
};

#endif // KALKABSTRACT_H

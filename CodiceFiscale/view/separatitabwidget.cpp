#include "separatitabwidget.h"

SeparatiTabWidget::SeparatiTabWidget() {
    cognomeEdit = new QLineEdit;
    QLabel* cognomeLabel = new QLabel(tr("&Cognome:"));
    cognomeLabel->setBuddy(cognomeEdit);

    nomeEdit = new QLineEdit;
    QLabel* nomeLabel = new QLabel(tr("&Nome:"));
    nomeLabel->setBuddy(nomeEdit);
    QPushButton* calcIden = new QPushButton(tr("Calcola"));
    QPushButton* cancIden = new QPushButton(tr("Cancella"));
    outIden = new QLineEdit;
    outIden->setReadOnly(true);
    connect(calcIden, SIGNAL(pressed()), this, SLOT(calcolaIden()));
    connect(cancIden, SIGNAL(pressed()), this, SLOT(pulisciIden()));

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    QFrame* line2 = new QFrame();
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);

    dataEdit = new QDateEdit;
    QLabel* dataLabel = new QLabel(tr("&Data di nascita:"));
    dataLabel->setBuddy(dataEdit);
    maschio = new QRadioButton(tr("&Maschio"), this);
    femmina = new QRadioButton(tr("&Femmina"), this);
    QLabel* sessoLabel = new QLabel(tr("&Sesso:"), this);
    maschio->toggle();
    sessoLabel->setBuddy(maschio);
    sessoLabel->setBuddy(femmina);
    QHBoxLayout* sesso = new QHBoxLayout;
    sesso->addWidget(maschio);
    sesso->addWidget(femmina);
    QPushButton* calcData = new QPushButton(tr("Calcola"));
    QPushButton* cancData = new QPushButton(tr("Cancella"));
    outData = new QLineEdit;
    outData->setReadOnly(true);
    connect(calcData, SIGNAL(pressed()), this, SLOT(calcolaData()));
    connect(cancData, SIGNAL(pressed()), this, SLOT(pulisciData()));

    menu = new QComboBox;
    std::vector<std::string> v = Nascita::getStati();
    for(std::vector<std::string>::const_iterator it = v.begin(); it != v.end(); ++it){
        menu->addItem(QString::fromStdString(*it));
    }

    menu->setEditable(true);
    menu->setCurrentText("ITALIA");
    menu->lineEdit()->setReadOnly(true);

    QLabel* statoLabel = new QLabel(tr("&Stato:"));
    statoLabel->setBuddy(menu);
    connect(menu, SIGNAL(activated(const QString&)), this, SLOT(onTextChanged(const QString&)));

    comuneEdit = new QLineEdit;
    QLabel* comuneLabel = new QLabel(tr("&Comune:"));
    comuneLabel->setBuddy(comuneEdit);

    provEdit = new QLineEdit;
    QLabel* provLabel = new QLabel(tr("&Provincia:"));
    provEdit->setMaxLength(2);
    provEdit->setFixedWidth(30);
    provLabel->setBuddy(provEdit);

    QPushButton* calcLuogo = new QPushButton(tr("Calcola"));
    QPushButton* cancLuogo = new QPushButton(tr("Cancella"));
    outLuogo = new QLineEdit;
    outLuogo->setReadOnly(true);
    connect(calcLuogo, SIGNAL(pressed()), this, SLOT(calcolaLuogo()));
    connect(cancLuogo, SIGNAL(pressed()), this, SLOT(pulisciLuogo()));

    QPushButton* calcola = new QPushButton(tr("Calcola tutto"));
    QPushButton* reset = new QPushButton(tr("Cancella tutto"));
    connect(calcola, SIGNAL(clicked()), this, SLOT(calcola()));
    connect(reset, SIGNAL(clicked()), this, SLOT(pulisci()));
    QHBoxLayout* footer = new QHBoxLayout;
    footer->addWidget(calcola);
    footer->addWidget(reset);

    QHBoxLayout* bottIden = new QHBoxLayout;
    bottIden->addWidget(calcIden);
    bottIden->addWidget(cancIden);
    QHBoxLayout* bottData = new QHBoxLayout;
    bottData->addWidget(calcData);
    bottData->addWidget(cancData);
    QHBoxLayout* bottLuogo = new QHBoxLayout;
    bottLuogo->addWidget(calcLuogo);
    bottLuogo->addWidget(cancLuogo);

    QGridLayout* body = new QGridLayout;
    body->addWidget(cognomeLabel, 0, 0);
    body->addWidget(cognomeEdit, 0, 1);
    body->addWidget(nomeLabel, 1, 0);
    body->addWidget(nomeEdit, 1, 1);
    body->addLayout(bottIden, 1, 2);
    body->addWidget(outIden, 1, 3);
    body->addWidget(line, 2, 0, 1, 4);
    body->addWidget(dataLabel, 3, 0);
    body->addWidget(dataEdit, 3, 1);
    body->addWidget(sessoLabel, 4, 0);
    body->addLayout(sesso, 4, 1);
    body->addLayout(bottData, 4, 2);
    body->addWidget(outData, 4, 3);
    body->addWidget(line2, 5, 0, 1, 4);
    body->addWidget(statoLabel, 6, 0);
    body->addWidget(menu, 6, 1);
    body->addWidget(comuneLabel, 7, 0);
    body->addWidget(comuneEdit, 7, 1);
    body->addWidget(provLabel, 8, 0);
    body->addWidget(provEdit, 8, 1);
    body->addLayout(bottLuogo, 8, 2);
    body->addWidget(outLuogo, 8, 3);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(body);
    mainLayout->addLayout(footer);
    setLayout(mainLayout);
}

// CONTROLLER

void SeparatiTabWidget::onTextChanged(const QString& s) {
    QString text = s.toUpper();
    if(text.compare("ITALIA") == 0) {
        provEdit->setReadOnly(false); // ora diventa modificabile
        provEdit->setStyleSheet("QLineEdit { background: rgb(255,255,255); }"); // color bianco di background
        comuneEdit->setReadOnly(false);
        comuneEdit->setStyleSheet("QLineEdit { background: rgb(255,255,255); }"); // color bianco di background
    } else { // se è qualsiasi cosa differente da "ITALIA" (anche solo "ITALI")
        provEdit->clear();
        comuneEdit->clear();
        provEdit->setReadOnly(true); // non modificabile
        provEdit->setStyleSheet("QLineEdit { background: rgb(211,211,211); }"); // color grigio di background
        comuneEdit->setReadOnly(true); // non modificabile
        comuneEdit->setStyleSheet("QLineEdit { background: rgb(211,211,211); }"); // color bianco di background
    }
}

void SeparatiTabWidget::calcolaIden() {
    try{
        QString cognome = cognomeEdit->text().toUpper();
        if(cognome.isEmpty()) throw Vuoto();
        std::string c = cognome.toStdString();
        c.erase(remove_if(c.begin(), c.end(), isspace), c.end());
        QString nome = nomeEdit->text().toUpper();
        if(nome.isEmpty()) throw Vuoto();
        std::string n = nome.toStdString();
        n.erase(remove_if(n.begin(), n.end(), isspace), n.end());
        Identificativo i(n, c);
        Soggetto::controllo(&i);
        outIden->setText(QString::fromStdString(i.generaCodice()));
    }
    catch(...) { outIden->setText("Errore!"); }
}

void SeparatiTabWidget::calcolaData() {
    QDate data = dataEdit->date();
    unsigned int gg = data.day();
    if(femmina->isChecked()) gg += 40;
    Data data_nascita(data.year(), data.month(), gg);

    outData->setText(QString::fromStdString(data_nascita.generaCodice()));
}

void SeparatiTabWidget::calcolaLuogo() {
    try{
        QString stato = menu->currentText().toUpper(); // estrae lo stato e lo trasforma in maiuscolo
        if(stato.isEmpty()) throw Vuoto(); // se vuoto lancia l'eccezione
        std::string luogo_nascita = stato.toStdString();
        if(stato.compare("ITALIA") == 0) {
            QString comune = comuneEdit->text().toUpper(); // estrae il comune e lo trasforma in maiuscolo
            QString provincia = provEdit->text().toUpper(); // estrae la provincia e lo trasforma in maiuscolo

            if(comune.isEmpty()) throw Vuoto(); // se vuoto lancia l'eccezione
            if(provincia.isEmpty()) throw Vuoto(); // se vuoto lancia l'eccezione

            luogo_nascita = comune.toStdString() + " (" + provincia.toStdString() + ")";
        }

        Nascita luogoNascita(Data(), luogo_nascita);
        Soggetto::controllo(&luogoNascita);
        outLuogo->setText(QString::fromStdString(luogoNascita.generaCodice()));
    }
    catch(...) { outLuogo->setText("Errore!"); }
}

void SeparatiTabWidget::calcola() {
    if(!cognomeEdit->text().isEmpty() || !nomeEdit->text().isEmpty()) calcolaIden();
    calcolaData();
    if(menu->currentText().toUpper().compare("ITALIA") != 0 || !(comuneEdit->text().isEmpty() && provEdit->text().isEmpty())) calcolaLuogo();
}

void SeparatiTabWidget::pulisciIden() {
    cognomeEdit->clear();
    nomeEdit->clear();
    outIden->clear();
}

void SeparatiTabWidget::pulisciData() {
    dataEdit->setDate(QDate(2000, 1, 1));
    maschio->setChecked(true);
    outData->clear();
}

void SeparatiTabWidget::pulisciLuogo() {
    menu->setCurrentText("ITALIA");
    comuneEdit->clear();
    comuneEdit->setReadOnly(false);
    comuneEdit->setStyleSheet("QLineEdit { background: rgb(255,255,255); }");
    provEdit->clear();
    provEdit->setReadOnly(false);
    provEdit->setStyleSheet("QLineEdit { background: rgb(255,255,255); }");
    outLuogo->clear();
}

void SeparatiTabWidget::pulisci() {
    pulisciIden();
    pulisciData();
    pulisciLuogo();
}

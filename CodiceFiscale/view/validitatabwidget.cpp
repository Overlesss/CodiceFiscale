#include "validitatabwidget.h"

ValiditaTabWidget::~ValiditaTabWidget() {}

ValiditaTabWidget::ValiditaTabWidget() {
    QLabel* valLabel = new QLabel(tr("Inserisci codice fiscale:"));
    valEdit = new QLineEdit;
    valEdit->setMaxLength(16); // massimo 16 caratteri
    valLabel->setBuddy(valEdit);

    out = new QTextEdit;
    out->setReadOnly(true);
    out->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    out->setFont(QFont("Times", 20));

    QPushButton* submit = new QPushButton(tr("Calcola"));
    connect(submit, SIGNAL(clicked()), this, SLOT(calcola()));
    connect(valEdit, SIGNAL(returnPressed()), this, SLOT(calcola()));

    QPushButton* reset = new QPushButton(tr("Cancella"));
    connect(reset, SIGNAL(clicked()), this, SLOT(pulisci()));

    QHBoxLayout* insert = new QHBoxLayout;
    insert->addWidget(valLabel);
    insert->addWidget(valEdit);

    QHBoxLayout* bottoni = new QHBoxLayout;
    bottoni->addWidget(submit);
    bottoni->addWidget(reset);

    QVBoxLayout* output = new QVBoxLayout;
    output->addWidget(out);

    QVBoxLayout* mainLayout = new QVBoxLayout;

    mainLayout->addLayout(insert);
    mainLayout->addLayout(bottoni);
    mainLayout->addLayout(output);

    setLayout(mainLayout);
}

// CONTROLLER

// slot che controlla se è valido il cf
void ValiditaTabWidget::calcola() throw (CfCorto) {
    QString str = valEdit->text().toUpper(); // estrae il codice fiscale inserito
    try{
        if(str.length() < 16) throw CfCorto(); // se non è di 16 caratteri, lancia eccezione
        CodiceFiscale cf(str.toStdString());

        const std::string cin_atteso = Soggetto::generaCodice(&cf);
        cf.controlloCin(cin_atteso);

        if(cf.controlloCin(cin_atteso)){
            out->setText("Codice fiscale valido."); // output
            out->setStyleSheet("QTextEdit { color: rgb(0, 204, 0); }"); // colore del testo verde
        } else throw ErrCf();
    }
    catch(CfCorto) { out->setText("Input non corretto, codice fiscale troppo corto."); out->setStyleSheet("QTextEdit { color: rgb(204, 0, 0); }"); }
    catch(ErrCf) { out->setText("Codice fiscale non valido."); out->setStyleSheet("QTextEdit { color: rgb(204, 0, 0); }"); }
    catch(ErrFile) { out->setText("Errore nell'apertura del file belfiore.txt."); out->setStyleSheet("QTextEdit { color: rgb(204, 0, 0); }"); }
    catch(ErrBelfiore) { out->setText("Codice fiscale non valido."); out->setStyleSheet("QTextEdit { color: rgb(204, 0, 0); }"); }
}

void ValiditaTabWidget::pulisci() {
    valEdit->clear();
    out->clear();
}


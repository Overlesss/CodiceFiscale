#include "inversotabwidget.h"

InversoTabWidget::~InversoTabWidget() {}

InversoTabWidget::InversoTabWidget() {
    QLabel* invLabel = new QLabel(tr("Inserisci codice fiscale:"));
    invEdit = new QLineEdit;
    invEdit->setMaxLength(16);
    //invEdit->setFixedWidth(200);
    invLabel->setBuddy(invEdit);

    out = new QTextEdit;
    out->setReadOnly(true);
    out->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    out->setFont(QFont("Times", 20));

    QPushButton* submit = new QPushButton(tr("Calcola"));
    connect(submit, SIGNAL(clicked()), this, SLOT(calcola()));
    connect(invEdit, SIGNAL(returnPressed()), this, SLOT(calcola()));

    QPushButton* reset = new QPushButton(tr("Cancella"));
    connect(reset, SIGNAL(clicked()), this, SLOT(pulisci()));

    QVBoxLayout* output = new QVBoxLayout;
    output->addWidget(out);

    QHBoxLayout* insert = new QHBoxLayout;
    insert->addWidget(invLabel);
    insert->addWidget(invEdit);

    QHBoxLayout* bottoni = new QHBoxLayout;
    bottoni->addWidget(submit);
    bottoni->addWidget(reset);

    QVBoxLayout* mainLayout = new QVBoxLayout;

    mainLayout->addLayout(insert);
    mainLayout->addLayout(bottoni);
    mainLayout->addLayout(output);

    setLayout(mainLayout);
}

// CONTROLLER

bool InversoTabWidget::contiene(QFile* f, const QString str) {
    QString line;
    QTextStream in(f);
    do {
        line = in.readLine();
        if (line.contains(str)) {
            while(!line.contains("Luogo")) {
                line = in.readLine();
                out->append(line);
            }
            return true;
        }
    } while (!line.isNull());

    return false;
}

// slot che restituisce le informazioni
void InversoTabWidget::calcola() throw (CfCorto) {
    CodiceFiscale cf;
    Nascita datiNascita;
    Sesso sesso;

    out->clear(); // pulisce l'output
    out->setStyleSheet("QTextEdit { color: rgb(0, 0, 0); }");
    QString str = invEdit->text().toUpper(); // estrae l'input
    try{
        if(str.length() < 16) throw CfCorto(); // se lunghezza < 16 caratteri lancio l'eccezione

        QFile file("./data.txt");
        //if () throw fileNonTrovato();
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text) || !contiene(&file, str)) {
            // dati non precedentemente insieriti
            CodiceFiscale cf(str.toStdString());
            const std::string cin_atteso = Soggetto::generaCodice(&cf);
            cf.controlloCin(cin_atteso);

            if(cf.controlloCin(cin_atteso)){
                Soggetto anonimo = cf;
                std::string codNascita = cf.estraiCodAnno() + cf.estraiCodMese() + cf.estraiCodGiornoSesso() + cf.estraiCodLuogo();
                datiNascita = *(dynamic_cast<Nascita*>(anonimo.creaDaCodice(&datiNascita,codNascita)));
                std::string codGiornoSesso = cf.estraiCodGiornoSesso();
                sesso = *(dynamic_cast<Sesso*>(anonimo.creaDaCodice(&sesso,codGiornoSesso)));

                out->setText(QString::fromStdString(anonimo.getDati()));
            } else throw ErrCf();
        }

    }
    catch(CfCorto) { out->setText("Input non corretto, codice fiscale troppo corto."); out->setStyleSheet("QTextEdit { color: rgb(204, 0, 0); }"); }
    catch(ErrCf) { out->setText("Codice fiscale non valido."); out->setStyleSheet("QTextEdit { color: rgb(204, 0, 0); }"); }
    catch(ErrFile) { out->setText("Errore nell'apertura del file belfiore.txt."); out->setStyleSheet("QTextEdit { color: rgb(204, 0, 0); }"); }
    catch(ErrBelfiore) { out->setText("Codice fiscale non valido."); out->setStyleSheet("QTextEdit { color: rgb(204, 0, 0); }"); }
    catch(fileNonTrovato) { out->setText("file non trovato"); }
}

void InversoTabWidget::pulisci() {
    invEdit->clear();
    out->clear();
}

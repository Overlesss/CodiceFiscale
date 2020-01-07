#include "calcolotabwidget.h"

CalcoloTabWidget::~CalcoloTabWidget() {}

CalcoloTabWidget::CalcoloTabWidget() {
    file.setFileName("data.txt");
    fout.setDevice(&file);

    cognomeEdit = new QLineEdit;
    QLabel* cognomeLabel = new QLabel(tr("&Cognome:"));
    cognomeLabel->setBuddy(cognomeEdit); // collega la label al riespettivo edit
    connect(cognomeEdit, SIGNAL(textChanged(QString)), this, SLOT(nascondiBottoni(QString)));

    nomeEdit = new QLineEdit;
    QLabel* nomeLabel = new QLabel(tr("&Nome:"));
    nomeLabel->setBuddy(nomeEdit); // collega la label al riespettivo edit
    connect(nomeEdit, SIGNAL(textChanged(QString)), this, SLOT(nascondiBottoni(QString)));

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
    comuneLabel->setBuddy(comuneEdit); // collega la label al riespettivo edit
    connect(comuneEdit, SIGNAL(textChanged(QString)), this, SLOT(nascondiBottoni(QString)));

    provEdit = new QLineEdit;
    QLabel* provLabel = new QLabel(tr("&Provincia:"));
    provEdit->setMaxLength(2); // massimo 2 caratteri
    provEdit->setFixedWidth(30); // dimensione del textedit ridotta a 30 pixel
    provLabel->setBuddy(provEdit); // collega la label al riespettivo edit
    connect(provEdit, SIGNAL(textChanged(QString)), this, SLOT(nascondiBottoni(QString)));

    maschio = new QRadioButton(tr("&Maschio"));
    femmina = new QRadioButton(tr("&Femmina"));
    QLabel* sessoLabel = new QLabel(tr("&Sesso:"));
    maschio->toggle(); // impostato come default
    sessoLabel->setBuddy(maschio); // collega la label al riespettivo edit
    sessoLabel->setBuddy(femmina); // collega la label al riespettivo edit

    dataEdit = new QDateEdit;
    QLabel* dataLabel = new QLabel(tr("&Data di nascita:"));
    dataLabel->setBuddy(dataEdit); // collega la label al riespettivo edit

    //output
    QLabel* outLabel = new QLabel(tr("Il risultato è: "));
    outLabel->setBuddy(out);
    QFont font = outLabel->font();
    font.setPointSize(15);
    font.setBold(true);
    outLabel->setFont(font);
    out = new QTextEdit;
    out->setReadOnly(true); // bloccato da modifiche
    out->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken); // stile della TextEdit
    out->setFont(QFont("Times", 20)); // imposta font dell'output e grandezza

    QPushButton* submit = new QPushButton(tr("Calcola"));
    connect(submit, SIGNAL(clicked()), this, SLOT(calcola())); // una volta cliccato esegue calculateResult

    QPushButton* reset = new QPushButton(tr("Cancella"));
    connect(reset, SIGNAL(clicked()), this, SLOT(pulisci())); // una volta cliccato resetta il form

    copy = new QPushButton(tr("Copia codice fiscale"));
    connect(copy, SIGNAL(clicked()), this, SLOT(copia()));
    copy->setVisible(false);
    save = new QPushButton(tr("Salva dati"));
    connect(save, SIGNAL(clicked()), this, SLOT(salva()));
    save->setVisible(false);
    clear = new QPushButton(tr("Pulisci file"));
    connect(clear, SIGNAL(clicked()), this, SLOT(pulisciFile()));

    QHBoxLayout* bottoni = new QHBoxLayout;
    QVBoxLayout* footer = new QVBoxLayout;
    QGridLayout* body = new QGridLayout;
    QVBoxLayout* sesso = new QVBoxLayout;
    QVBoxLayout* output = new QVBoxLayout;
    QHBoxLayout* bottoniOut = new QHBoxLayout;

    sesso->addWidget(maschio);
    sesso->addWidget(femmina);

    bottoni->addWidget(submit);
    bottoni->addWidget(reset);

    // layout a griglia 3x3
    body->addWidget(cognomeLabel, 0, 0);
    body->addWidget(cognomeEdit, 0, 1);
    body->addWidget(nomeLabel, 0, 2);
    body->addWidget(nomeEdit, 0, 3);
    body->addWidget(statoLabel, 1, 0);
    body->addWidget(menu, 1, 1);
    body->addWidget(comuneLabel, 2, 0);
    body->addWidget(comuneEdit, 2, 1);
    body->addWidget(provLabel, 2, 2);
    body->addWidget(provEdit, 2, 3);
    body->addWidget(sessoLabel, 3, 0);
    body->addLayout(sesso, 3, 1);;
    body->addWidget(dataLabel, 3, 2);
    body->addWidget(dataEdit, 3, 3);

    footer->addLayout(bottoni);

    output->addWidget(outLabel);
    output->addWidget(out);

    bottoniOut->addWidget(copy);
    bottoniOut->addWidget(save);
    bottoniOut->addWidget(clear);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(body);
    mainLayout->addLayout(footer);
    mainLayout->addLayout(output);
    mainLayout->addLayout(bottoniOut);
    setLayout(mainLayout);
}

// CONTROLLER

// slot che sblocca comuneEdit e provEdit se statoEdit è "italia", case insensitive
void CalcoloTabWidget::onTextChanged(const QString& s) {
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

    copy->setVisible(false);
    save->setVisible(false);
}

// slot che calcola il codice fiscale
void CalcoloTabWidget::calcola() throw(Vuoto) {
    Soggetto s;
    try{
        //antroponimo
        QString cognome = cognomeEdit->text().toUpper(); // estrae il dato di cognomeEdit e lo trasforma in maiuscolo
        if(cognome.isEmpty()) throw Vuoto('c', out); // se vuoto lancio eccezione
        QString nome = nomeEdit->text().toUpper(); // estrae il dato di nomeEdit e lo trasforma in maiuscolo
        if(nome.isEmpty()) throw Vuoto('n', out); // se vuoto lancio eccezione
        std::string n = nome.toStdString();
        n.erase(remove_if(n.begin(), n.end(), isspace), n.end()); // cancella gli spazi
        std::string c = cognome.toStdString();
        c.erase(remove_if(c.begin(), c.end(), isspace), c.end()); // cancella gli spazi
        Identificativo individuo(n, c);
        Soggetto::controllo(&individuo); // controlla eventuali errori
        s.assegna(&individuo);

        //sesso
        Sesso sesso;
        if(maschio->isChecked()) sesso = 'm';
        else sesso = 'f';
        s.assegna(&sesso);

        //data
        QDate data = dataEdit->date(); // estrae la data
        Data data_nascita(data.year(), data.month(), data.day());

        //luogo
        QString stato = menu->currentText().toUpper(); // estrae lo stato e lo trasforma in maiuscolo
        if(stato.isEmpty()) throw Vuoto('s', out); // se vuoto lancia l'eccezione
        std::string luogo_nascita = stato.toStdString();
        if(stato.compare("ITALIA") == 0) {
            QString comune = comuneEdit->text().toUpper(); // estrae il comune e lo trasforma in maiuscolo
            QString provincia = provEdit->text().toUpper(); // estrae la provincia e lo trasforma in maiuscolo

            if(comune.isEmpty()) throw Vuoto('o', out); // se vuoto lancia l'eccezione
            if(provincia.isEmpty()) throw Vuoto('p', out); // se vuoto lancia l'eccezione

            luogo_nascita = comune.toStdString() + " (" + provincia.toStdString() + ")";
        }

        Nascita data_luogo_nascita(data_nascita, luogo_nascita);
        Soggetto::controllo(&data_luogo_nascita);

        CodiceFiscale cf;
        Soggetto s(data_luogo_nascita, sesso, individuo);
        std::string cod = Soggetto::generaCodice(&individuo) + Soggetto::generaCodice(&data_luogo_nascita);
        std::string codS = Soggetto::generaCodice(&sesso);
        if(codS != "0") {
            unsigned int g = data_luogo_nascita.estraiGiorno();
            g = g + DatiPersona::stringToUInt(codS);
            cod.replace(9,2,DatiPersona::uintToString(g));
        }
        CodiceFiscale cfTemp = cod; //cfTemp composto da 15 caratteri
        cod.append(Soggetto::generaCodice(&cfTemp));
        cf.creaDaCodice(cod);

        s.assegna(&cf);

        QString result = QString::fromStdString(cf.estraiCodice()); // trasforma il cf da std::string a QString
        out->setStyleSheet("QTextEdit { color: rgb(0, 0, 0); }"); // imposta colore scritte in nero
        out->setText(result); // output

        copy->setVisible(true);
        save->setVisible(true);
        clear->setVisible(true);
    }
    catch(Vuoto) { out->append("Errore!"); out->setStyleSheet("QTextEdit { color: rgb(204, 0, 0); }"); }
    catch(ErrAntr) { out->setText("Nome o cognome non validi."); out->setStyleSheet("QTextEdit { color: rgb(204, 0, 0); }"); }
    catch(ErrData) { out->setText("Data errata."); out->setStyleSheet("QTextEdit { color: rgb(204, 0, 0); }");} // ???
    catch(ErrLuogo) { out->setText("Luogo inesistente."); out->setStyleSheet("QTextEdit { color: rgb(204, 0, 0); }");}
    catch(ErrFile) { out->setText("Errore nell'apertura del file belfiore.txt."); out->setStyleSheet("QTextEdit { color: rgb(204, 0, 0); }");}
}

// slot che resetta il form
void CalcoloTabWidget::pulisci() {
    nomeEdit->clear();
    cognomeEdit->clear();
    menu->setCurrentText("ITALIA");
    comuneEdit->clear();
    comuneEdit->setReadOnly(false);
    comuneEdit->setStyleSheet("QLineEdit { background: rgb(255,255,255); }");
    provEdit->clear();
    provEdit->setReadOnly(false);
    provEdit->setStyleSheet("QLineEdit { background: rgb(255,255,255); }");
    maschio->toggle();
    dataEdit->setDate(QDate(2000, 1, 1)); // imposta la data di default
    out->clear();
    copy->setVisible(false);
    save->setVisible(false);
}

// slot che copia il codice fiscale negli appunti
void CalcoloTabWidget::copia() {
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString cf = out->toPlainText();

    clipboard->setText(cf, QClipboard::Clipboard);
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(tr("Testo copiato negli appunti"));
    msgBox.exec();
}

// slot che salva i dati in un file txt
void CalcoloTabWidget::salva() {
    QMessageBox msgBox;
    msgBox.resize(800, 100);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("I dati verranno salvati.");
    msgBox.setInformativeText("Vuoi continuare?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
        case QMessageBox::Save:

            QString cf = out->toPlainText();
            QString cognome = cognomeEdit->text().toUpper();
            QString nome = nomeEdit->text().toUpper();
            QString sesso;
            if(maschio->isChecked()) sesso = "Maschio";
            else sesso = "Femmina";
            QDate data = dataEdit->date();
            QString dataStr;
            dataStr.append(QString::number(data.day()) + "/");
            dataStr.append(QString::number(data.month()) + "/");
            dataStr.append(QString::number(data.year()));
            QString stato = menu->currentText().toUpper();
            QString luogo_nascita = stato;
            if(stato.compare("ITALIA") == 0) {
                QString comune = comuneEdit->text().toUpper();
                QString provincia = provEdit->text().toUpper();

                luogo_nascita = comune + " (" + provincia + ")";
            }
            try{
                if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) throw fileNonTrovato();
            }
            catch(fileNonTrovato) { out->setText("File non trovato."); }

            fout << cf << "\n";
            fout << "Cognome: " << cognome << "\n";
            fout << "Nome: " << nome << "\n";
            fout << "Sesso: " << sesso << "\n";
            fout << "Data di nascita: " << dataStr << "\n";
            fout << "Luogo di nascita: " << luogo_nascita << "\n";
            fout << "====================================================================" << "\n";

            file.close();

        break;

    }
}

void CalcoloTabWidget::pulisciFile() {
    file.resize(0);
    QMessageBox msgBox;
    msgBox.setStyleSheet("QLabel{min-width: 4em;}");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(tr("File pulito"));
    msgBox.exec();
}

void CalcoloTabWidget::nascondiBottoni(QString str) {
    copy->setVisible(false);
    save->setVisible(false);
}


#include "mainwindow.h"

MainWindow::~MainWindow() {}

MainWindow::MainWindow(QWidget* parent) : QDialog(parent) {
    QWidget::setWindowTitle(tr("KALK: Codice fiscale")); // imposta titolo finestra
    QWidget::resize(800, 480); // imposta dimensioni

    QTabWidget* tab = new QTabWidget;
    tab->addTab(new CalcoloTabWidget(), tr("Calcolo codice fiscale")); // aggiunge tab di calcolo
    tab->addTab(new ValiditaTabWidget(), tr("Validità codice")); // aggiunge tab di validità
    tab->addTab(new InversoTabWidget(), tr("Codice fiscale inverso")); // aggiunge tab per l'inverso
    tab->addTab(new SeparatiTabWidget(), tr("Calcolo codici singoli")); // aggiunge tab per l'inverso

    QDialogButtonBox* exit = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(exit, &QDialogButtonBox::rejected, this, &QDialog::reject); // bottone che fa uscire

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tab);
    mainLayout->addWidget(exit);
    setLayout(mainLayout);
}


#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "calcolotabwidget.h"
#include "validitatabwidget.h"
#include "inversotabwidget.h"
#include "separatitabwidget.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QTabWidget>
#include <QVBoxLayout>

class MainWindow : public QDialog {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
};

#endif // MYWIDGET_H

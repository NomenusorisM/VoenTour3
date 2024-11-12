#ifndef MAIN_FORM_H
#define MAIN_FORM_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QVector>
#include <QLine>
#include <QPoint>
#include <QIODevice>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>

#include "form.h"
#include "ui_main_form.h"
#include "json_io.h"
#include "BuildPathTable.h"

namespace Ui {
class MainForm;
}

class MainForm : public QDialog
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = nullptr);
    ~MainForm();

private slots:
    void handleStartButtonClicked();
    void handleImportButtonClicked();

private:
    Ui::MainForm *ui;
    Form *field_dlg;

    InputValues _input;
};

#endif // MAIN_FORM_H

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

#include "field.h"
#include "main_form.h"
#include "ui_main_form.h"
#include "fill_utils.h"
#include "PathFinding.h"

namespace Ui {
class MainForm;
}

struct InputFile
{
    int squads_cnt;
    QPoint dest_cords;
    QVector<QPoint> squad_cords;
    QVector<int> squad_types;
    QVector<int> squad_speeds;
    QVector<int> squad_fuel_consumption;
    int roads_cnt;
    QVector<QLine> roads_cords;
};

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
    Field *field_dlg;
    InputFile input_conf;
};

#endif // MAIN_FORM_H

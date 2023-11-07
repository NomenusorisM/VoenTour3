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

namespace Ui {
class MainForm;
}

struct InputFile
{
    int squads_cnt;
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
    InputFile input_conf;

    void fillArray(QStringList &list, QVector<int> &array);
    void fillArray(QStringList &list, QVector<QPoint> &array);
    void fillArray(QStringList &list, QVector<QLine> &array);
};

#endif // MAIN_FORM_H

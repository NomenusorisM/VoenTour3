#ifndef FORM_OLD_H
#define FORM_OLD_H

#include <QWidget>
#include "json_io.h"

namespace Ui
{
    class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    Form(
        StationsArray stations,
        DelaysArray connections,
        QWidget *parent = nullptr);
    ~Form();

protected:
    void paintEvent(QPaintEvent *event) override;
    void drawConnections(QPainter &painter);
    void drawStations(QPainter &painter);
    void drawGrid(QPainter &painter);

private:
    Ui::Form *ui;

    StationsArray stations;
    DelaysArray connections;
};

#endif // FORM_OLD_H

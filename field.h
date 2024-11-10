#ifndef FIELD_OLD_H
#define FIELD_OLD_H

#include <QWidget>
#include "json_io.h"

namespace Ui {
class Field;
}

class Field : public QWidget
{
    Q_OBJECT

public:
    Field(
        StationsArray stations,
        DelaysArray connections,
        QWidget *parent = nullptr
        );
    ~Field();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::Field *ui;

    StationsArray stations;
    DelaysArray connections;
};

#endif // FIELD_OLD_H

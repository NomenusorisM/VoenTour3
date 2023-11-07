#ifndef FIELD_OLD_H
#define FIELD_OLD_H

#include <QWidget>

namespace Ui {
class Field;
}

class Field : public QWidget
{
    Q_OBJECT

public:
    Field(
        QVector<QLine> roads,
        QVector<QPoint> positions,
        QVector<QLine> routes,
        QPoint mainPoint,
        QWidget *parent = nullptr
        );
    ~Field();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::Field *ui;

    QVector<QLine> roads;
    QVector<QPoint> positions;
    QVector<QLine> routes;
    QPoint mainPoint;
};

#endif // FIELD_OLD_H

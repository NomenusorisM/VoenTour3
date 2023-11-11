#include "ui_field.h"
#include <QPainter>
#include "field.h"

Field::Field(
    QVector<QLine> roads,
    QVector<QPoint> positions,
    QVector<QLine> routes,
    QPoint mainPoint,
    QWidget *parent
    ) :
    QWidget(parent),
    ui(new Ui::Field)
{
    ui->setupUi(this);

    this->roads = roads;
    this->positions = positions;
    this->routes = routes;
    this->mainPoint = mainPoint;
}

Field::~Field()
{
    delete ui;
}

void Field::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.scale(10.0, 10.0);
    QPen pen;

    // Отрисовываем дороги
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    for(auto road: roads)
        painter.drawLine(road);

    // Отрисовываем пути
    pen.setColor(Qt::green);
    pen.setWidth(1);
    painter.setPen(pen);
    for(auto route: routes)
        painter.drawLine(route);

    // Отрисовываем позиции
    pen.setColor(Qt::blue);
    pen.setWidth(3);
    painter.setPen(pen);
    for(auto pos: positions)
        painter.drawPoint(pos);

    // Отрисовываем базу
    pen.setColor(Qt::red);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawPoint(mainPoint);
}

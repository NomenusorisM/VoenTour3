#include "field.h"
#include "ui_field.h"
#include "qpainter.h"

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
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(3);

    // Отрисовываем дороги
    for(auto road: roads)
        painter.drawLine(road);

    // Отрисовываем базу
    pen.setColor(Qt::red);
    pen.setWidth(7);
    painter.drawPoint(mainPoint);

    // Отрисовываем позиции
    pen.setColor(Qt::blue);
    pen.setWidth(5);
    for(auto pos: positions)
        painter.drawPoint(pos);

    // Отрисовываем пути
    pen.setColor(Qt::green);
    pen.setWidth(1);
    for(auto route: routes)
        painter.drawLine(route);
}

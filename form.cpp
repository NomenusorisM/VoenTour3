#include "ui_form.h"
#include <QPainter>
#include "form.h"
#include "json_io.h"

Form::Form(
    StationsArray stations,
    DelaysArray connections,
    QWidget *parent
    ) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    this->stations = stations;
    this->connections = connections;
}

Form::~Form()
{
    delete ui;
}

void Form::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawGrid(painter);
    drawStations(painter);
    drawConnections(painter);
}

void Form::drawGrid(QPainter &painter)
{
    const int gridSize = 40;
    const int numCells = 8;

    QPen gridPen(QColor(200, 200, 200));
    painter.setPen(gridPen);

    for (int i = 0; i <= numCells; ++i) {
        int x = i * gridSize;
        int y = i * gridSize;

        painter.drawLine(x, 0, x, gridSize * numCells);
        painter.drawLine(0, y, gridSize * numCells, y);
    }

    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);

    for (int i = 0; i < numCells; ++i) {
        char letter = 'A' + i;
        painter.drawText(i * gridSize + 10, 15, QString(letter));
    }

    for (int i = 0; i < numCells; ++i) {
        painter.drawText(10, i * gridSize + 25, QString::number(i + 1));
    }
}

void Form::drawStations(QPainter &painter)
{
    const int gridSize = 40;

    QPen stationPen(Qt::blue);
    stationPen.setWidth(5);
    painter.setPen(stationPen);

    for (const auto& station : stations) {
        int x = station.cord[0] - 'A';
        int y = station.cord[1] - '1';

        painter.drawPoint(x * gridSize + gridSize / 2, y * gridSize + gridSize / 2);
    }
}

void Form::drawConnections(QPainter &painter)
{
    const int gridSize = 40;

    QPen connectionPen(Qt::red);
    connectionPen.setWidth(2);

    for (const auto& delay : connections) {
        painter.setPen(connectionPen);
        const station_t* station1 = nullptr;
        const station_t* station2 = nullptr;

        for (const auto& station : stations) {
            if (station.id == delay.id_1) {
                station1 = &station;
            }
            if (station.id == delay.id_2) {
                station2 = &station;
            }
        }

        if (station1 && station2) {
            int x1 = station1->cord[0] - 'A';
            int y1 = station1->cord[1] - '1';
            int x2 = station2->cord[0] - 'A';
            int y2 = station2->cord[1] - '1';

            painter.drawLine(x1 * gridSize + gridSize / 2, y1 * gridSize + gridSize / 2,
                             x2 * gridSize + gridSize / 2, y2 * gridSize + gridSize / 2);

            int midX = (x1 + x2) * gridSize / 2 + gridSize / 2;
            int midY = (y1 + y2) * gridSize / 2 + gridSize / 2;

            QFont font = painter.font();
            font.setPointSize(8);
            painter.setFont(font);
            painter.setPen(Qt::black);
            painter.drawText(midX, midY - 5, QString::number(delay.del));
        }
    }
}

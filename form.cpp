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
    painter.setRenderHint(QPainter::Antialiasing); // Для сглаживания

    // Рисуем координатную сетку
    drawGrid(painter);

    // Отрисовываем станции
    drawStations(painter);

    // Отрисовываем соединения
    drawConnections(painter);
}

// Метод для отрисовки сетки с буквами и цифрами
void Form::drawGrid(QPainter &painter)
{
    const int gridSize = 40;  // Размер ячеек сетки
    const int numCells = 8;  // Количество ячеек по каждой оси

    QPen gridPen(QColor(200, 200, 200));
    painter.setPen(gridPen);

    // Рисуем вертикальные и горизонтальные линии сетки
    for (int i = 0; i <= numCells; ++i) {
        int x = i * gridSize;
        int y = i * gridSize;

        // Вертикальные линии
        painter.drawLine(x, 0, x, gridSize * numCells);
        // Горизонтальные линии
        painter.drawLine(0, y, gridSize * numCells, y);
    }

    // Рисуем метки координат
    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);

    // Метки по горизонтали (буквы)
    for (int i = 0; i < numCells; ++i) {
        char letter = 'A' + i;
        painter.drawText(i * gridSize + 10, 15, QString(letter));
    }

    // Метки по вертикали (цифры)
    for (int i = 0; i < numCells; ++i) {
        painter.drawText(10, i * gridSize + 25, QString::number(i + 1));
    }
}

// Метод для отрисовки станций
void Form::drawStations(QPainter &painter)
{
    const int gridSize = 40;  // Размер ячеек сетки

    QPen stationPen(Qt::blue);
    stationPen.setWidth(5);
    painter.setPen(stationPen);

    for (const auto& station : stations) {
        // Преобразуем координаты станции из "A1", "D4" в индексы
        int x = station.cord[0] - 'A';  // Преобразуем букву в индекс по оси X
        int y = station.cord[1] - '1';  // Преобразуем цифру в индекс по оси Y

        // Рисуем точку станции
        painter.drawPoint(x * gridSize + gridSize / 2, y * gridSize + gridSize / 2);
    }
}

// Метод для отрисовки соединений между станциями и отображения задержек
void Form::drawConnections(QPainter &painter)
{
    const int gridSize = 40;  // Размер ячеек сетки

    QPen connectionPen(Qt::black);
    connectionPen.setWidth(2);
    painter.setPen(connectionPen);

    // Проходим по всем задержкам и рисуем линии между станциями
    for (const auto& delay : connections) {
        // Находим станции по их id
        const station_t* station1 = nullptr;
        const station_t* station2 = nullptr;

        // Ищем станции с id_1 и id_2
        for (const auto& station : stations) {
            if (station.id == delay.id_1) {
                station1 = &station;
            }
            if (station.id == delay.id_2) {
                station2 = &station;
            }
        }

        // Если обе станции найдены, рисуем соединение между ними
        if (station1 && station2) {
            // Преобразуем координаты станций из "A1", "D4" в индексы
            int x1 = station1->cord[0] - 'A';
            int y1 = station1->cord[1] - '1';
            int x2 = station2->cord[0] - 'A';
            int y2 = station2->cord[1] - '1';

            // Рисуем линию между станциями
            painter.drawLine(x1 * gridSize + gridSize / 2, y1 * gridSize + gridSize / 2,
                             x2 * gridSize + gridSize / 2, y2 * gridSize + gridSize / 2);

            // Рассчитываем середину линии для текста (задержки)
            int midX = (x1 + x2) * gridSize / 2 + gridSize / 2;
            int midY = (y1 + y2) * gridSize / 2 + gridSize / 2;

            // Отображаем задержку на середине линии
            QFont font = painter.font();
            font.setPointSize(8);
            painter.setFont(font);
            painter.setPen(Qt::red);  // Цвет текста (красный)
            painter.drawText(midX, midY - 5, QString::number(delay.del));
        }
    }
}

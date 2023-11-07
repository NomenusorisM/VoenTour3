#include "main_form.h"
#include "ui_main_form.h"

MainForm::MainForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    this->input_conf = InputFile();

    connect(ui->importPushButton, SIGNAL(clicked()), this, SLOT(handleImportButtonClicked()));
    connect(ui->startPushButton, SIGNAL(clicked()), this, SLOT(handleStartButtonClicked()));
}

void MainForm::fillArray(QStringList &list, QVector<int> &array)
{
    for (int i = 0; i < list.size(); ++i)
    {
        bool is_ok = true;
        array.push_back(list[i].toInt(&is_ok));
        if (!is_ok) { qDebug() << "Convert error"; }
    }
}

void MainForm::fillArray(QStringList &list, QVector<QPoint> &array)
{
    for (int i = 0; i < list.size(); ++i)
    {
        bool is_ok = true;

        auto cord_paths = list[i].split(";");

        array.push_back(QPoint(cord_paths[0].toInt(), cord_paths[1].toInt()));

        if (!is_ok) { qDebug() << "Convert error"; }
    }
}

void MainForm::fillArray(QStringList &list, QVector<QLine> &array)
{
    for (int i = 0; i < list.size(); ++i)
    {
        bool is_ok = true;

        auto cord_paths = list[i].split(";");

        const auto start = QPoint(cord_paths[0].toInt(), cord_paths[1].toInt());
        const auto end = QPoint(cord_paths[2].toInt(), cord_paths[3].toInt());

        auto line = QLine(start, end);

        array.push_back(line);

        if (!is_ok) { qDebug() << "Convert error"; }
    }
}

void MainForm::handleStartButtonClicked()
{
    field_dlg = new Field(
        input_conf.roads_cords,
        input_conf.squad_cords,
        input_conf.roads_cords,
        input_conf.dest_cords
        );

    field_dlg->show();
}

void MainForm::handleImportButtonClicked()
{
    QString file_path = QFileDialog::getOpenFileName(this,
                                                    QString::fromUtf8("Открыть файл"),
                                                    QDir::currentPath(),
                                                    "Text (*.txt)");

    if (file_path.length() == 0)
        return;

    QFile input_file(file_path);

    if (input_file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&input_file);
        QString line;
        QStringList parts;

        // read squads_cnt
        line = in.readLine();
        input_conf.squads_cnt = line.toInt();

        // read dest_cords
        line = in.readLine();
        parts = line.split(";");
        input_conf.dest_cords = QPoint(parts[0].toInt(), parts[1].toInt());

        // read squad_cords
        line = in.readLine();
        parts = line.split(" ");
        fillArray(parts, input_conf.squad_cords);

        // read squad_types
        line = in.readLine();
        parts = line.split(" ");
        fillArray(parts, input_conf.squad_types);

        // read squad_speed
        line = in.readLine();
        parts = line.split(" ");
        fillArray(parts, input_conf.squad_speeds);

        // read squad_fuel_consumption
        line = in.readLine();
        parts = line.split(" ");
        fillArray(parts, input_conf.squad_fuel_consumption);

        // read roads_cnt
        line = in.readLine();
        input_conf.roads_cnt = line.toInt();

        // read roads_cords
        line = in.readLine();
        parts = line.split(" ");
        fillArray(parts, input_conf.roads_cords);

        ui->startPushButton->setEnabled(true);
    }

    else
    {
        QMessageBox::critical(this, "Ошибка при импорте", "Не удалось открыть выбранный файл");
    }
}

MainForm::~MainForm()
{
    delete field_dlg;
    delete ui;
}

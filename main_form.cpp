#include "main_form.h"

MainForm::MainForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    this->input_conf = InputFile();

    connect(ui->importPushButton, SIGNAL(clicked()), this, SLOT(handleImportButtonClicked()));
    connect(ui->startPushButton, SIGNAL(clicked()), this, SLOT(handleStartButtonClicked()));
}

QVector<int> MainForm::GetFuelConsumption(QVector<int> &path_lengths)
{
    QVector<int> fuel_consumptions;

    for (int i(0); i < path_lengths.size(); i++)
    {
        fuel_consumptions.push_back(path_lengths[i] * input_conf.squad_fuel_consumption[i]);
    }

    return fuel_consumptions;
}

float MainForm::GetMaxTime(QVector<int> &path_lengths)
{
    int maximal = -10000;

    for (int i(0); i < path_lengths.size(); i++)
        maximal = std::max(path_lengths[i] / input_conf.squad_speeds[i], maximal);

    return maximal;
}

void MainForm::WriteAnswers(QVector<int> &fuel_consumptions, int max_time)
{
    QString fuel_consumptions_result;

    for (int i(0); i < fuel_consumptions.size(); i++)
        fuel_consumptions_result += (QString("%1").arg(fuel_consumptions[i]) + " ");

    fuel_consumptions_result.chop(1);

    qDebug() << fuel_consumptions_result;

    QString filename = "OUTPUT.TXT";
    QFile file( filename );
    if ( file.open(QIODevice::WriteOnly) )
    {
        qDebug() << 1;
        QTextStream stream( &file );
        stream << fuel_consumptions_result << '\n';
        stream << QString("%1").arg(max_time);
    }
}

void MainForm::handleStartButtonClicked()
{
    auto shortest_path = WaveAlgo(input_conf.squads_cnt, input_conf.dest_cords, input_conf.squad_cords, input_conf.roads_cnt, input_conf.roads_cords);

    QVector<QLine> shortest_roads;
    QVector<int> path_lenghts;

    std::tie(shortest_roads, path_lenghts) = shortest_path;

    auto fuel_consumtpions = GetFuelConsumption(path_lenghts);
    auto max_time = GetMaxTime(path_lenghts);

    WriteAnswers(fuel_consumtpions, max_time);

    this->field_dlg = new Field(
        input_conf.roads_cords,
        input_conf.squad_cords,
        shortest_roads,
        input_conf.dest_cords
        );

    this->field_dlg->show();
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

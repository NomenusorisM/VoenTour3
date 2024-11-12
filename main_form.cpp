#include "main_form.h"

MainForm::MainForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    connect(ui->importPushButton, SIGNAL(clicked()), this, SLOT(handleImportButtonClicked()));
    connect(ui->startPushButton, SIGNAL(clicked()), this, SLOT(handleStartButtonClicked()));
}

void MainForm::handleStartButtonClicked()
{
    // ------ Отрисовка карты
    this->field_dlg = new Form(_input.first, _input.second);
    this->field_dlg->show();
    // ------

    // ------ Формироание отчета
    OutputValues output = BuildPathTable(_input.first.size(), _input.first, _input.second);
    writeOutputFile("OUTPUT.json", output);
    // ------
}

void MainForm::handleImportButtonClicked()
{
    QString file_path = QFileDialog::getOpenFileName(this,
                                                    QString::fromUtf8("Открыть файл"),
                                                    QDir::currentPath(),
                                                    "JSON (*.json)");

    if (file_path.length() == 0)
        return;

    auto inputRead = readInputFile(file_path);

    if (inputRead.second) {
        _input = inputRead.first;
        ui->startPushButton->setEnabled(true);
    } else {
        QMessageBox::critical(this, "Ошибка при импорте", "Не удалось открыть выбранный файл");
    }
}

MainForm::~MainForm()
{
    delete field_dlg;
    delete ui;
}

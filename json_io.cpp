#include "json_io.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QPair>

static QPair<QJsonDocument, bool>
readJsonFromFile(const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл:" << filePath;
        return QPair<QJsonDocument, bool>(QJsonDocument(), false);
    }

    // Чтение содержимого файла
    QByteArray fileData = file.readAll();
    file.close();

    // Преобразование содержимого файла в JSON документ
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);

    if (jsonDoc.isNull()) {
        qWarning() << "Ошибка при разборе JSON файла";
        return QPair<QJsonDocument, bool>(QJsonDocument(), false);
    }

    return QPair<QJsonDocument, bool>(jsonDoc, true);
}

QPair<InputValues, bool>
readInputFile(const QString& filePath) {
    auto readPair = readJsonFromFile(filePath);

    if (!readPair.second) {
        qWarning() << "Не удалось считать JSON файл";
        return QPair<InputValues, bool>(InputValues(), false);
    }

    uint8_t stationsCount = readPair.first["stations_cnt"].toInt();
    QJsonArray stationsArray = readPair.first["stations"].toArray();
    QJsonArray delaysArray = readPair.first["delays"].toArray();

    // ------------ Импорт станций
    StationsArray stations;
    stations.reserve(stationsCount);

    for (const QJsonValue &stationValue : stationsArray) {
        QJsonObject stationObj = stationValue.toObject();

        station_t station;
        station.id = static_cast<uint32_t>(stationObj["name"].toInt());

        QString cordStr = stationObj["cord"].toString();
        strncpy(station.cord, cordStr.toStdString().c_str(), sizeof(station.cord) - 1);
        station.cord[sizeof(station.cord) - 1] = '\0'; // Ensure null-terminated

        station.chains_cnt = static_cast<uint32_t>(stationObj["chain_cnt"].toInt());

        stations.push_back(station);
    }
    // ------------

    // ------------ Импорт задержек
    DelaysArray delays;
    for (const QJsonValue &delayValue : delaysArray) {
        QJsonObject delayObj = delayValue.toObject();

        delay_t delay;
        delay.id_1 = static_cast<uint32_t>(delayObj["name_1"].toInt());
        delay.id_2 = static_cast<uint32_t>(delayObj["name_2"].toInt());
        delay.del = static_cast<uint32_t>(delayObj["delay"].toInt());

        delays.push_back(delay);
    }
    // ------------

    return QPair<InputValues, bool>(InputValues(stations, delays), true);
}

bool
writeOutputFile(const QString& filePath, const OutputValues& values) {
    QJsonArray jsonArray;

    for (const auto& path : values) {
        QJsonObject jsonObj;
        jsonObj["target_station"] = static_cast<int>(path.target_station_id);
        jsonObj["sum_delay"] = static_cast<int>(path.sum_delay);
        jsonObj["first_station"] = static_cast<int>(path.first_station_id);

        jsonArray.append(jsonObj);
    }

    QJsonDocument jsonDoc(jsonArray);

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDoc.toJson());
        file.close();
    } else {
        qWarning("Не удалось открыть файл для записи");
        return false;
    }

    return true;
}

#include "fill_utils.h"

void fillArray(QStringList &list, QVector<int> &array)
{
    for (int i = 0; i < list.size(); ++i)
    {
        bool is_ok = true;
        array.push_back(list[i].toInt(&is_ok));
        if (!is_ok) { qDebug() << "Convert error"; }
    }
}

void fillArray(QStringList &list, QVector<QPoint> &array)
{
    for (int i = 0; i < list.size(); ++i)
    {
        bool is_ok = true;

        auto cord_paths = list[i].split(";");

        array.push_back(QPoint(cord_paths[0].toInt(), cord_paths[1].toInt()));

        if (!is_ok) { qDebug() << "Convert error"; }
    }
}

void fillArray(QStringList &list, QVector<QLine> &array)
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

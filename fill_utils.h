#ifndef FILL_UTILS_H
#define FILL_UTILS_H

#include <QLine>
#include <QPoint>
#include <QVector>
#include <QStringList>
#include <QDebug>

void fillArray(QStringList &list, QVector<QLine> &array);

void fillArray(QStringList &list, QVector<QPoint> &array);

void fillArray(QStringList &list, QVector<int> &array);

#endif // FILL_UTILS_H

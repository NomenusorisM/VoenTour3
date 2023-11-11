#pragma once

#include <QVector>
#include <QLine>
#include <QPoint>
#include <tuple>

#define maxcoord 101

typedef std::tuple <QVector<QLine>, QVector<int>> PathAlgoResult;


PathAlgoResult WaveAlgo( int , QPoint, QVector<QPoint>, int , QVector<QLine> );

int find_path( int paths_matrix[][maxcoord], QPoint start_pos, QPoint finish_point, QVector<QLine>& );

void generate_paths_matrix( QVector <QLine> &roads, int paths[][maxcoord]);

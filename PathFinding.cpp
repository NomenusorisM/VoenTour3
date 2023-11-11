#define _CRT_SECURE_NO_WARNINGS

#include "PathFinding.h"

PathAlgoResult WaveAlgo( int N_p, QVector<int> finish_pos, QVector<QPoint> start_pos, int N_r, QVector<QLine> roads)
{

	QLine Temp_line;
	QPoint Temp_point;

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    int paths_matrix[maxcoord][maxcoord] = { 0 };

	QVector <QLine> shortest_paths;
	QVector <int> path_lengths;

	QPoint finish_point = { -1, -1 };

	generate_paths_matrix(roads, paths_matrix);

	for( int i = 0; i < N_p; i++ )
	{
		path_lengths.push_back(find_path( paths_matrix, start_pos[i], finish_point, shortest_paths ));
	}

    return std::make_tuple( shortest_paths, path_lengths );;
}


void generate_paths_matrix( QVector <QLine>& roads, int paths[][maxcoord] )
{
    for(int i = 0; i < roads.size(); i++ )
    {
        for( int j = roads[i].x1; j <= roads[i].x2; j++ )
        {
            for( int k = roads[i].y1; k <= roads[i].y2; k++ )
			{
                paths[k][j] = 1;
			}
		}
	}
}

int find_path( int paths_matrix[][maxcoord], struct QPoint start_pos, struct QPoint finish_point, QVector<QLine> &shortest_paths )
{
    int DRP[maxcoord][maxcoord] = { 0 };
    int waving = 1;
    int start_x = start_pos.x, start_y = start_pos.y, end_x = finish_point.x, end_y = finish_point.y;
    int x, y;
    int wave = 1;
    int LEN=0;
    int x_prev, y_prev;
	QLine direction;
	DRP[start_y][start_x] = 1;

	while( waving )
	{
		waving = 0;
		for( int i = 0; ( i < maxcoord ) && ( ( end_x + end_y ) < 2 * maxcoord - 2 ); i++ )
		{
			for( int j = 0; ( j < maxcoord ) && ( ( end_x + end_y ) < 2 * maxcoord - 2 ); j++ )
			{
				if( DRP[i][j] == wave )
				{
					waving = 1;
					if( ( i == end_y ) && ( j == end_x ) )
					{
						printf( "Waves to reach finish: %d\n", DRP[i][j] - 1 );
						LEN = DRP[i][j] - 1;
						waving = 0;
						break;
					}
					if( ( ( i + 1 ) < maxcoord ) && ( DRP[i + 1][j] == 0 ) && ( paths_matrix[i + 1][j] == 1 ) ) DRP[i + 1][j] = wave + 1;
					if( ( ( i - 1 ) >= 0 ) && ( DRP[i - 1][j] == 0 ) && ( paths_matrix[i - 1][j] == 1 ) ) DRP[i - 1][j] = wave + 1;
					if( ( ( j + 1 ) < maxcoord ) && ( DRP[i][j + 1] == 0 ) && ( paths_matrix[i][j+1] == 1 ) ) DRP[i][j + 1] = wave + 1;
					if( ( ( j - 1 ) >= 0 ) && ( DRP[i][j - 1] == 0 ) && ( paths_matrix[i][j-1] == 1 ) ) DRP[i][j - 1] = wave + 1;
				}
			}
		}
		wave++;
	}
	x = end_x;
	y = end_y;
	if( x + y > 2 * maxcoord - 2 ) return 0;
	wave = DRP[end_y][end_x];
	x_prev = end_x;
	y_prev = end_y;
	while( 1 )
	{
		if( ( ( y + 1 ) < maxcoord ) && ( DRP[y + 1][x] == wave - 1 ) )
		{
			if( ( x == start_x ) && ( (y) == start_y ) ) break;
			direction = { x_prev, y_prev, x, y + 1 };
			y++;
		}
		else if( ( ( y - 1 ) >= 0 ) && ( DRP[y - 1][x] == wave - 1 ) )
		{
			if( ( x == start_x ) && ( (y) == start_y ) ) break;
			direction = { x_prev, y_prev, x, y - 1 };
			y--;
		}
		else if( ( ( x + 1 ) < maxcoord ) && ( DRP[y][x + 1] == wave - 1 ) )
		{
			if( ( (x) == start_x ) && ( y == start_y ) ) break;
			direction = { x_prev, y_prev, x+1, y };
			x++;
		}
		else if( ( ( x - 1 ) >= 0 ) && ( DRP[y][x - 1] == wave - 1 ) )
		{
			if( ( (x) == start_x ) && ( y == start_y ) ) break;
			direction = { x_prev, y_prev, x-1, y };
			x--;
		}
		x_prev = x;
		y_prev = y;
		wave--;
		shortest_paths.push_back( direction );
	}
	return LEN;
}

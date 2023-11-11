#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

#define maxcoord 101

std::tuple <Qvector<QLine>, Qvector<int>> RETURN;

int WaveAlgo( int , Qvector<QPoint>, int , Qvector<QLine> );

short find_path( short paths_matrix[][maxcoord], QPoint start_pos, QPoint finish_point, Qvector<QLine>& );

void generate_paths_matrix( Qvector <QLine> &roads, short paths[][maxcoord] );

int WaveAlgo( int N_p, Qvector<int> finish_pos, Qvector<QPoint> start_pos, int N_r, Qvector<QLine> roads)
{

	QLine Temp_line;
	QPoint Temp_point;

	short x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	short paths_matrix[maxcoord][maxcoord] = { 0 };

	Qvector <QLine> shortest_paths;
	Qvector <int> path_lengths;

	QPoint finish_point = { -1, -1 };

	generate_paths_matrix(roads, paths_matrix);

	/*for( int i = 0; i < maxcoord; i++ ) {
		for( int j = 0; j < maxcoord; j++ ) {
			printf( "%d", paths_matrix[i][j] );
		}
		printf( "\n" );
	}*/

	for( int i = 0; i < N_p; i++ )
	{
		path_lengths.push_back(find_path( paths_matrix, start_pos[i], finish_point, shortest_paths ));
	}

	RETURN = make_tuple( shortest_paths, path_lengths );

	return 0;
}


void generate_paths_matrix( Qvector <QLine>& roads, short paths[][maxcoord] )
{
	for( short i = 0; i < roads.size(); i++ )
	{
		for( short x = roads[i].x1; x <= roads[i].x2; x++ )
		{
			for( short y = roads[i].y1; y <= roads[i].y2; y++ )
			{
				paths[y][x] = 1;
			}
		}
	}
}

short find_path( short paths_matrix[][maxcoord], struct QPoint start_pos, struct QPoint finish_point, Qvector<QLine> &shortest_paths )
{
	short DRP[maxcoord][maxcoord] = { 0 };
	short waving = 1;
	short start_x = start_pos.x, start_y = start_pos.y, end_x = finish_point.x, end_y = finish_point.y;
	short x, y;
	short wave = 1;
	short LEN=0;
	short x_prev, y_prev;
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
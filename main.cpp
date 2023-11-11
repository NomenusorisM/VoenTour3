#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>


#define maxcoord 101

struct QPoint
{
	short x = -1;
	short y = -1;
};

struct QLine
{
	short x1 = -1;
	short y1 = -1;
	short x2 = -1;
	short y2 = -1;
};

std::tuple <std::vector<QLine>, std::vector<int>> RETURN;

short find_path( short paths_matrix[][maxcoord], QPoint start_pos, QPoint finish_point, std::vector<QLine>& );

void generate_paths_matrix( std::vector <QLine>& roads, short paths[][maxcoord] );

int main()
{
	std::ifstream inp( "a.txt" );

	QLine Temp_line;
	QPoint Temp_point;

	short N_p = 0;
	short N_r = 0;
	short x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	short paths_matrix[maxcoord][maxcoord] = { 0 };
	std::vector <QLine> roads;
	std::vector <QPoint> start_pos;

	std::vector <QLine> shortest_paths;
	std::vector <int> path_lengths;

	QPoint finish_point = { -1, -1 };

	if( inp.is_open() )
	{
		inp >> N_p;
		inp >> finish_point.x >> finish_point.y;
		for( int i = 0; i < N_p; i++ )
		{
			inp >> Temp_point.x >> Temp_point.y;
			start_pos.push_back( Temp_point );
		}
		inp >> N_r;
		for( int i = 0; i < N_r; i++ )
		{
			inp >> Temp_line.x1 >> Temp_line.y1 >> Temp_line.x2 >> Temp_line.y2;
			roads.push_back( Temp_line );
		}
	}

	generate_paths_matrix( roads, paths_matrix );

	/*for( int i = 0; i < maxcoord; i++ ) {
		for( int j = 0; j < maxcoord; j++ ) {
			printf( "%d", paths_matrix[i][j] );
		}
		printf( "\n" );
	}*/

	for( int i = 0; i < N_p; i++ )
	{
		path_lengths.push_back( find_path( paths_matrix, start_pos[i], finish_point, shortest_paths ) );
	}

	RETURN = make_tuple( shortest_paths, path_lengths );

	return 0;
}


void generate_paths_matrix( std::vector <QLine>& roads, short paths[][maxcoord] )
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

short find_path( short paths_matrix[][maxcoord], struct QPoint start_pos, struct QPoint finish_point, std::vector<QLine>& shortest_paths )
{
	short DRP[maxcoord][maxcoord] = { 0 };
	short waving = 1;
	short start_x = start_pos.x, start_y = start_pos.y, end_x = finish_point.x, end_y = finish_point.y;
	short x, y;
	short wave = 1;
	short LEN = 0;
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
					if( ( ( j + 1 ) < maxcoord ) && ( DRP[i][j + 1] == 0 ) && ( paths_matrix[i][j + 1] == 1 ) ) DRP[i][j + 1] = wave + 1;
					if( ( ( j - 1 ) >= 0 ) && ( DRP[i][j - 1] == 0 ) && ( paths_matrix[i][j - 1] == 1 ) ) DRP[i][j - 1] = wave + 1;
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
			if( ( x == start_x ) && ( ( y ) == start_y ) ) break;
			direction = { x_prev, y_prev, x, y + 1 };
			y++;
		}
		else if( ( ( y - 1 ) >= 0 ) && ( DRP[y - 1][x] == wave - 1 ) )
		{
			if( ( x == start_x ) && ( ( y ) == start_y ) ) break;
			direction = { x_prev, y_prev, x, y - 1 };
			y--;
		}
		else if( ( ( x + 1 ) < maxcoord ) && ( DRP[y][x + 1] == wave - 1 ) )
		{
			if( ( ( x ) == start_x ) && ( y == start_y ) ) break;
			direction = { x_prev, y_prev, x + 1, y };
			x++;
		}
		else if( ( ( x - 1 ) >= 0 ) && ( DRP[y][x - 1] == wave - 1 ) )
		{
			if( ( ( x ) == start_x ) && ( y == start_y ) ) break;
			direction = { x_prev, y_prev, x - 1, y };
			x--;
		}
		x_prev = x;
		y_prev = y;
		wave--;
		shortest_paths.push_back( direction );
	}
	return LEN;
}
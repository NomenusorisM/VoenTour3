#include "BuildPathTable.h"

OutputValues BuildPathTable( uint32_t RaschetNumber, StationsArray Stations, std::vector<DelaysArray> Connections )
{
    OutputValues Output( MAX_STATIONS );
    PathLenMatrix_t PathMatrix[MAX_STATIONS];
    int32_t ConnectionsMatrix[MAX_STATIONS][MAX_STATIONS];

    for( int i = 0; i < MAX_STATIONS; i++ )
    {
        for( int j = 0; j < MAX_STATIONS; j++ )
        {
            if( i == j ) ConnectionsMatrix[i][j] = 0;
            else ConnectionsMatrix[i][j] = -1;
        }
    }

    for( int i = 0; i < RaschetNumber; i++ )
    {
        for( int j = 0; j < Stations[i].chains_cnt; j++ )
        {
            ConnectionsMatrix[i][Get_Station_Index( RaschetNumber, Stations, Connections[i][j].id_2 )] = Connections[i][j].del;
        }
    }

    PathMatrix[0].path_len = 0;
    PathMatrix[0].first_station_index = 0;

    for( int i = 1; i < MAX_STATIONS; i++ )
    {
        PathMatrix[i].path_len = UINT32_MAX;
    }

    for( int i = 0; i < Stations[0].chains_cnt; i++ )
    {
        uint32_t current_station = Get_Station_Index( RaschetNumber, Stations, Connections[0][i].id_2 );
        PathMatrix[current_station].first_station_index = current_station;
        PathMatrix[current_station].path_len = ConnectionsMatrix[0][current_station];
    }

    for( int i = 0; i < Stations[0].chains_cnt; i++ )
    {
        uint32_t current_station = Get_Station_Index( RaschetNumber, Stations, Connections[0][i].id_2 );
        UpdatePathMatrix( ConnectionsMatrix, PathMatrix, current_station );
    }

    for( int i = 0; i < RaschetNumber; i++ )
    {
        Output[i].first_station_id = Stations[PathMatrix[i].first_station_index].id;
        Output[i].sum_delay = PathMatrix[i].path_len;
        Output[i].target_station_id = Stations[i].id;
    }

    return Output;
}

uint32_t Get_Station_Index( uint32_t RaschetNumber, StationsArray Stations, uint32_t Station_Id )
{
    for( int i = 0; i < RaschetNumber; i++ )
    {
        if( Stations[i].id == Station_Id ) {
            return i;
        }
    }
    return -1;
}

void UpdatePathMatrix( int32_t ConnectionsMatrix[][MAX_STATIONS], PathLenMatrix_t PathMatrix[], uint32_t current_station )
{
    uint32_t next_station = 0;
    for( int i = 0; i < MAX_STATIONS; i++ )
    {
        if( ConnectionsMatrix[current_station][i] != -1 )
        {
            next_station = i;
            if( PathMatrix[next_station].path_len > ( PathMatrix[current_station].path_len + ConnectionsMatrix[current_station][next_station] ) )
            {
                PathMatrix[next_station].path_len = PathMatrix[current_station].path_len + ConnectionsMatrix[current_station][next_station];
                PathMatrix[next_station].first_station_index = PathMatrix[current_station].first_station_index;
                UpdatePathMatrix( ConnectionsMatrix, PathMatrix, next_station );
            }
        }
    }
}
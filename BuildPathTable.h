#ifndef BUILD_PATH_TABLE_H
#define BUILD_PATH_TABLE_H

#define MAX_STATIONS 20

#include "json_io.h"
#include <fstream>
#include <tuple>

typedef struct
{
    uint32_t path_len;
    uint32_t first_station_index;
} PathLenMatrix_t;

std::vector<message_path_t> BuildPathTable( uint32_t RaschetNumber, StationsArray Stations, DelaysArray Connections );
uint32_t Get_Station_Index( uint32_t RaschetNumber, StationsArray Stations, uint32_t Station_Id );
void UpdatePathMatrix( int32_t ConnectionsMatrix[][MAX_STATIONS], PathLenMatrix_t PathMatrix[], uint32_t current_station );

#endif
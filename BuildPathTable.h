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

extern OutputValues
BuildPathTable(uint32_t RaschetNumber, const StationsArray& Stations, const DelaysArray& Connections);

#endif

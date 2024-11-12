#ifndef JSON_IO_H
#define JSON_IO_H

#include <stdint.h>
#include <vector>
#include <QString>
#include <QPair>

typedef struct {
    uint32_t id;
    char cord[3];
    uint32_t chains_cnt;
} station_t;

typedef struct {
    uint32_t id_1;
    uint32_t id_2;
    uint32_t del;
} delay_t;

typedef struct {
    uint32_t target_station_id;
    uint32_t sum_delay;
    uint32_t first_station_id;
} message_path_t;

using StationsArray = std::vector<station_t>;
using DelaysArray = std::vector<delay_t>;

using InputValues = std::pair<StationsArray, DelaysArray>;
using OutputValues = std::vector<message_path_t>;

QPair<InputValues, bool>
readInputFile(const QString& filePath);

bool
writeOutputFile(const QString& filePath, const OutputValues& values);

#endif // JSON_IO_H

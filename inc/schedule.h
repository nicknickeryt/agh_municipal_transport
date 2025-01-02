#pragma once

#include "line.h"
#include "stop.h"
#include <vector>

class Schedule {
public:
    static void printScheduleForStop(const Stop& stop, const std::vector<Line>& lines);
    static void printScheduleForStop(const Stop& stop, const Line& line);
};
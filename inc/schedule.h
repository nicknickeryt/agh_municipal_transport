#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <map>
#include <vector>
#include <string>

using std::vector;
using std::map;
using std::string;

class Schedule {
public:
  static map<Direction, vector<string>>
  getLineScheduleForStop(Line& line, int stopId, ScheduleDay day);

  static map<ScheduleDay, map<Direction, vector<string>>>
  getLineScheduleForStop(Line& line, int stopId);

  static map<Line, map<ScheduleDay, map<Direction, vector<string>>>>
  getAllSchedulesForStop(int stopId, vector<Line> &lines);
};

#endif // SCHEDULE_H
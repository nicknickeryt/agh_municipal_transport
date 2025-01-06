#pragma once

using namespace std;

class Schedule {
public:
  static map<Direction, vector<string>>
  getLineScheduleForStop(Line line, int stopId, ScheduleDay day);

  static map<ScheduleDay, map<Direction, vector<string>>>
  getLineScheduleForStop(Line line, int stopId);

  static map<Line, map<ScheduleDay, map<Direction, vector<string>>>>
  getAllSchedulesForStop(int stopId, vector<Line *> &lines);
};
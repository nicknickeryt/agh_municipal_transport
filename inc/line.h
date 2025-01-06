#pragma once

#include <map>
#include <vector>

#include "stop.h"
#include "utils.h"

using namespace std;

class Line {
private:
  int number;
  vector<Stop> route;
  map<ScheduleDay, map<Direction, map<Stop, vector<string>>>> schedule;

public:
  Line(int number, vector<Stop> route);

  int getNumber() const;
  void setNumber(int number);

  vector<Stop> getRoute();
  void setRoute(vector<Stop> route);

  map<ScheduleDay, map<Direction, map<Stop, vector<string>>>> getSchedule();
  void setSchedule(
      map<ScheduleDay, map<Direction, map<Stop, vector<string>>>> schedule);

  map<Direction, map<Stop, vector<string>>> getSchedule(ScheduleDay day);

  void setSchedule(ScheduleDay day,
                   map<Direction, map<Stop, vector<string>>> schedule);

  map<Stop, vector<string>> getSchedule(ScheduleDay day, Direction direction);
  void setSchedule(ScheduleDay day, Direction direction,
                   map<Stop, vector<string>> schedule);

  string getTargetStop(Direction direction) const;

  bool operator<(const Line &other) const;
};
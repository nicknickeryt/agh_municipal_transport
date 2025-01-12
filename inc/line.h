#pragma once

#include <map>
#include <vector>

#include "stop.h"
#include "utils.h"

using namespace std;

class Line
{
private:
  int number;
  vector<int> route; // Changed from vector<Stop> to vector<int>
  map<ScheduleDay, map<Direction, map<int, vector<string>>>> schedule; // Changed Stop to int

public:
  Line(int number);
  Line(int number, vector<int> &route); // Changed vector<Stop> to vector<int>

  int getNumber() const;
  void setNumber(int number);

  vector<int> getRoute(); // Changed vector<Stop> to vector<int>
  void setRoute(vector<int> &route); // Changed vector<Stop> to vector<int>
  bool hasStop(int stopId);

  map<ScheduleDay, map<Direction, map<int, vector<string>>>> getSchedule(); // Changed Stop to int
  void setSchedule(
      map<ScheduleDay, map<Direction, map<int, vector<string>>>> schedule); // Changed Stop to int

  map<Direction, map<int, vector<string>>> getSchedule(ScheduleDay day); // Changed Stop to int

  void setSchedule(ScheduleDay day,
                   map<Direction, map<int, vector<string>>> schedule); // Changed Stop to int

  void setSchedule(ScheduleDay day, Direction direction, int stopId, vector<string> times); // Changed Stop to int

  map<int, vector<string>> getSchedule(ScheduleDay day, Direction direction); // Changed Stop to int
  void setSchedule(ScheduleDay day, Direction direction,
                   map<int, vector<string>> schedule); // Changed Stop to int

  int getTargetStop(Direction direction) const; // Changed Stop to int

  bool operator<(const Line &other) const;

  static Line &getLineById(vector<Line> &lines, int id);
};

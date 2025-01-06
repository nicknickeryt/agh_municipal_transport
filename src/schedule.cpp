#include <map>
#include <vector>
#include <iostream>

#include "line.h"
#include "schedule.h"
#include "stop.h"
#include "utils.h"

using namespace std;

map<Direction, vector<string>>
Schedule::getLineScheduleForStop(Line line, int stopId, ScheduleDay day) {
  map<Direction, vector<string>> schedule;
  for (auto direction : {Direction::A, Direction::B}) {
    for (auto [stop, times] : line.getSchedule(day, direction)) {
      if (stop.getId() == stopId)
        schedule[direction] = times;
    }
  }
  return schedule;
}

map<ScheduleDay, map<Direction, vector<string>>>
Schedule::getLineScheduleForStop(Line line, int stopId) {
  map<ScheduleDay, map<Direction, vector<string>>> schedule;
  for (auto day :
       {ScheduleDay::WORKDAY, ScheduleDay::SATURDAY, ScheduleDay::HOLIDAY}) {
    schedule[day] = getLineScheduleForStop(line, stopId, day);
  }
  return schedule;
}

map<Line, map<ScheduleDay, map<Direction, vector<string>>>>
Schedule::getAllSchedulesForStop(int stopId, vector<Line *> &lines) {
  map<Line, map<ScheduleDay, map<Direction, vector<string>>>> schedule;
  for (auto &line : lines) {
    schedule[*line] = getLineScheduleForStop(*line, stopId);
  }
  return schedule;
}
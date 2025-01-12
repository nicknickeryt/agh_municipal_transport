#include <bits/stdc++.h>
#include <map>
#include <vector>

#include "line.h"
#include "stop.h"
#include "utils.h"

using namespace std;

Line::Line(int number, vector<int> &route) : number(number), route(route) {}
Line::Line(int number) : number(number) {}

int Line::getNumber() const { return number; }
void Line::setNumber(int number) { this->number = number; }

vector<int> Line::getRoute() { return route; }
void Line::setRoute(vector<int> &route) { this->route = route; }

bool Line::hasStop(int stopId) {
  return count(route.begin(), route.end(), stopId);
}

map<ScheduleDay, map<Direction, map<int, vector<string>>>> Line::getSchedule() {
  return schedule;
}
void Line::setSchedule(
    map<ScheduleDay, map<Direction, map<int, vector<string>>>> schedule) {
  this->schedule = schedule;
}

map<Direction, map<int, vector<string>>> Line::getSchedule(ScheduleDay day) {
  return schedule[day];
}
void Line::setSchedule(ScheduleDay day,
                       map<Direction, map<int, vector<string>>> schedule) {
  this->schedule[day] = schedule;
}

map<int, vector<string>> Line::getSchedule(ScheduleDay day,
                                           Direction direction) {
  return schedule[day][direction];
}
void Line::setSchedule(ScheduleDay day, Direction direction,
                       map<int, vector<string>> schedule) {
  this->schedule[day][direction] = schedule;
}

void Line::setSchedule(ScheduleDay day, Direction direction, int stop,
                       vector<string> times) {
  schedule[day][direction][stop] = times;
}

int Line::getTargetStop(Direction direction) const {
  return direction == Direction::A ? route.back() : route.front();
}

bool Line::operator<(const Line &other) const { return number < other.number; }

Line &Line::getLineById(vector<Line> &lines, int id) {
  for (Line &line : lines) {
    if (line.getNumber() == id) {
      return line;
    }
  }
  throw runtime_error("Line with the given ID not found");
}
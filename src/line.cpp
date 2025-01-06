#include <map>
#include <vector>

#include "line.h"
#include "stop.h"
#include "utils.h"

using namespace std;

Line::Line(int number, vector<Stop> route) : number(number), route(route) {}

int Line::getNumber() const { return number; }
void Line::setNumber(int number) { this->number = number; }

vector<Stop> Line::getRoute() { return route; }
void Line::setRoute(vector<Stop> route) { this->route = route; }

map<ScheduleDay, map<Direction, map<Stop, vector<string>>>>
Line::getSchedule() {
  return schedule;
}
void Line::setSchedule(
    map<ScheduleDay, map<Direction, map<Stop, vector<string>>>> schedule) {
  this->schedule = schedule;
}

map<Direction, map<Stop, vector<string>>> Line::getSchedule(ScheduleDay day) {
  return schedule[day];
}
void Line::setSchedule(ScheduleDay day,
                       map<Direction, map<Stop, vector<string>>> schedule) {
  this->schedule[day] = schedule;
}

map<Stop, vector<string>> Line::getSchedule(ScheduleDay day,
                                            Direction direction) {
  return schedule[day][direction];
}
void Line::setSchedule(ScheduleDay day, Direction direction,
                       map<Stop, vector<string>> schedule) {
  this->schedule[day][direction] = schedule;
}

string Line::getTargetStop(Direction direction) const {
  return direction == Direction::A ? route.back().getName()
                                   : route.front().getName();
}

bool Line::operator<(const Line &other) const { return number < other.number; }
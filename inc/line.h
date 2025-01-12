#ifndef LINE_H
#define LINE_H

#include <map>
#include <vector>

#include <boost/serialization/map.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

#include "stop.h"
#include "utils.h"

using std::map;
using std::vector;
using std::string;

class Line {
private:
  int number;
  vector<int> route;
  map<ScheduleDay, map<Direction, map<int, vector<string>>>> schedule;

public:
  Line() = default;
  Line(int number);
  Line(int number, vector<int> &route);

  int getNumber() const;
  void setNumber(int number);

  vector<int> getRoute();
  void setRoute(vector<int> &route);
  bool hasStop(int stopId);

  map<ScheduleDay, map<Direction, map<int, vector<string>>>> getSchedule();
  void setSchedule(
      map<ScheduleDay, map<Direction, map<int, vector<string>>>> schedule);

  map<Direction, map<int, vector<string>>> getSchedule(ScheduleDay day);
  void setSchedule(ScheduleDay day,
                   map<Direction, map<int, vector<string>>> schedule);

  void setSchedule(ScheduleDay day, Direction direction, int stopId,
                   vector<string> times);

  map<int, vector<string>> getSchedule(ScheduleDay day,
                                            Direction direction);
  void setSchedule(ScheduleDay day, Direction direction,
                   map<int, vector<string>> schedule);

  int getTargetStop(Direction direction) const;

  bool operator<(const Line &other) const;

  static Line &getLineById(vector<Line> &lines, int id);

  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    (void)version;
    ar & number;
    ar & route;
    ar & schedule;
  }
};

#endif // LINE_H
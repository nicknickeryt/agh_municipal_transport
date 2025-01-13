#ifndef LINE_H
#define LINE_H

#include <map>
#include <vector>

#include <boost/serialization/map.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

#include "stop.h"
#include "enums.h"

using std::map;
using std::string;
using std::vector;

/**
 * @brief Represents a transport line.
 */
class Line {
private:
  int number;
  TransportType lineType;
  vector<int> route;
  map<ScheduleDay, map<Direction, map<int, vector<string>>>> schedule;

public:
  /**
   * @brief Default constructor.
   */
  Line() = default;

  /**
   * @brief Parameterized constructor.
   * @param number Line number.
   * @param lineType Type of transport for the line.
   */
  Line(int number, TransportType lineType);

  /**
   * @brief Parameterized constructor with route.
   * @param number Line number.
   * @param lineType Type of transport for the line.
   * @param route Route of the line, represented by stop IDs.
   */
  Line(int number, TransportType lineType, vector<int> &route);

  /**
   * @brief Get the line number.
   * @return The line number.
   */
  int getNumber() const;

  /**
   * @brief Set the line number.
   * @param number The new line number.
   */
  void setNumber(int number);

  /**
   * @brief Get the type of transport for the line.
   * @return The type of transport for the line.
   */
  TransportType getType() const;

  /**
   * @brief Get the type of transport as a string.
   * @return The type of transport as a string.
   */
  string getTypeString() const;

  /**
   * @brief Set the type of transport for the line.
   * @param type The new type of transport for the line.
   */
  void setType(TransportType type);

  /**
   * @brief Get the route of the line.
   * @return The route of the line, represented by stop IDs.
   */
  vector<int> getRoute();

  /**
   * @brief Set the route of the line.
   * @param route The new route of the line, represented by stop IDs.
   */
  void setRoute(vector<int> &route);

  /**
   * @brief Check if the line has a specific stop.
   * @param stopId The ID of the stop to check.
   * @return True if the line has the stop, false otherwise.
   */
  bool hasStop(int stopId);

  /**
   * @brief Get the schedule of the line.
   * @return The schedule of the line.
   */
  map<ScheduleDay, map<Direction, map<int, vector<string>>>> getSchedule();

  /**
   * @brief Set the schedule of the line.
   * @param schedule The new schedule of the line.
   */
  void setSchedule(map<ScheduleDay, map<Direction, map<int, vector<string>>>> schedule);

  /**
   * @brief Get the schedule of the line for a specific day.
   * @param day The day for which to get the schedule.
   * @return The schedule of the line for the specified day.
   */
  map<Direction, map<int, vector<string>>> getSchedule(ScheduleDay day);

  /**
   * @brief Set the schedule of the line for a specific day.
   * @param day The day for which to set the schedule.
   * @param schedule The new schedule for the specified day.
   */
  void setSchedule(ScheduleDay day, map<Direction, map<int, vector<string>>> schedule);

  /**
   * @brief Set the schedule of the line for a specific day, direction, and stop.
   * @param day The day for which to set the schedule.
   * @param direction The direction for which to set the schedule.
   * @param stopId The ID of the stop for which to set the schedule.
   * @param times The new schedule times for the specified stop.
   */
  void setSchedule(ScheduleDay day, Direction direction, int stopId, vector<string> times);

  /**
   * @brief Get the schedule of the line for a specific day and direction.
   * @param day The day for which to get the schedule.
   * @param direction The direction for which to get the schedule.
   * @return The schedule of the line for the specified day and direction.
   */
  map<int, vector<string>> getSchedule(ScheduleDay day, Direction direction);

  /**
   * @brief Set the schedule of the line for a specific day and direction.
   * @param day The day for which to set the schedule.
   * @param direction The direction for which to set the schedule.
   * @param schedule The new schedule for the specified day and direction.
   */
  void setSchedule(ScheduleDay day, Direction direction, map<int, vector<string>> schedule);

  /**
   * @brief Get the target stop for a specific direction.
   * @param direction The direction for which to get the target stop.
   * @return The ID of the target stop for the specified direction.
   */
  int getTargetStop(Direction direction) const;

  /**
   * @brief Comparison operator for sorting lines.
   * @param other The other line to compare with.
   * @return True if this line is less than the other line, false otherwise.
   */
  bool operator<(const Line &other) const;

  /**
   * @brief Get a line by its ID from a vector of lines.
   * @param lines The vector of lines.
   * @param id The ID of the line to find.
   * @return A reference to the line with the given ID.
   */
  static Line &getLineById(vector<Line> &lines, int id);

  /**
   * @brief Serialization function for Boost.Serialization.
   * @param ar The archive to serialize to.
   * @param version The version of the serialization.
   */
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    (void)version;
    ar & number;
    ar & lineType;
    ar & route;
    ar & schedule;
  }
};

#endif // LINE_H
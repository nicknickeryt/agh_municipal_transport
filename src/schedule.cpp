#include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <vector>

#include "line.h"
#include "schedule.h"
#include "stop.h"
#include "utils.h"

using std::map;
using std::set;
using std::string;
using std::vector;

map<Direction, vector<string>>
Schedule::getLineScheduleForStop(Line &line, int stopId, ScheduleDay day) {
  map<Direction, vector<string>> schedule;
  for (auto direction : {Direction::A, Direction::B}) {
    for (auto [scheduleStopId, times] : line.getSchedule(day, direction)) {
      if (scheduleStopId == stopId)
        schedule[direction] = times;
    }
  }
  return schedule;
}

map<ScheduleDay, map<Direction, vector<string>>>
Schedule::getLineScheduleForStop(Line &line, int stopId) {
  map<ScheduleDay, map<Direction, vector<string>>> schedule;
  for (auto day :
       {ScheduleDay::WORKDAY, ScheduleDay::SATURDAY, ScheduleDay::HOLIDAY}) {
    schedule[day] = getLineScheduleForStop(line, stopId, day);
  }
  return schedule;
}

map<Line, map<ScheduleDay, map<Direction, vector<string>>>>
Schedule::getAllSchedulesForStop(int stopId, vector<Line> &lines) {
  map<Line, map<ScheduleDay, map<Direction, vector<string>>>> schedule;
  for (auto &line : lines) {
    if (line.hasStop(stopId))
      schedule[line] = getLineScheduleForStop(line, stopId);
  }
  return schedule;
}

vector<map<Line, pair<int, int>>>
Schedule::findConnection(int startStopId, int endStopId, vector<Line> &lines) {
  vector<map<Line, pair<int, int>>> connections;
  set<int> visitedStops;
  visitedStops.insert(startStopId);

  // Recursive helper function
  std::function<bool(int, int, Line *, int &)> findPath =
      [&](int currentStopId, int targetStopId, Line *currentLine,
          int &segmentStart) -> bool {
    for (Line &line : lines) {
      auto route = line.getRoute();

      // Check if the current stop is on this line's route
      if (std::find(route.begin(), route.end(), currentStopId) != route.end()) {
        // If the target stop is on this line, we can create a direct connection
        if (std::find(route.begin(), route.end(), targetStopId) !=
            route.end()) {
          if (currentLine != &line) {
            // If we're switching lines, push the previous connection
            if (currentLine) {
              connections.push_back(
                  {{*currentLine, {segmentStart, currentStopId}}});
            }
            segmentStart = currentStopId; // Start a new segment on the new line
          }
          connections.push_back(
              {{line,
                {segmentStart, targetStopId}}}); // Push the final connection
          return true;                           // Target reached
        }

        // Continue exploring the route
        for (int transferStopId : route) {
          if (visitedStops.find(transferStopId) == visitedStops.end()) {
            visitedStops.insert(transferStopId);

            if (currentLine != &line) {
              // If we're switching lines, push the previous connection
              if (currentLine) {
                connections.push_back(
                    {{*currentLine, {segmentStart, currentStopId}}});
              }
              segmentStart =
                  currentStopId; // Start a new segment on the new line
            }

            // Recurse to find the path from the transfer stop
            if (findPath(transferStopId, targetStopId, &line, segmentStart)) {
              return true; // Target reached
            }
          }
        }
      }
    }

    return false; // No path found
  };

  int segmentStart = startStopId;
  findPath(startStopId, endStopId, nullptr, segmentStart);

  // Check if the first and last stop IDs are equal to the given startStopId and
  // endStopId
  if (!connections.empty()) {
    auto firstConnection = connections.front().begin();
    auto lastConnection = connections.back().begin();

    if (firstConnection->second.first != startStopId ||
        lastConnection->second.second != endStopId) {
      connections.clear();
    }
  }

  return connections;
}

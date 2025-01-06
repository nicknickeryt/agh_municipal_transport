#include <iostream>
#include <vector>

#include "line.h"
#include "schedule.h"
#include "stop.h"
#include "utils.h"
#include "demo.h"

void Demo() {
  vector<Line *> lines;

  Stop plac = Stop("Plac Centralny", 1);
  Stop dworzec = Stop("Dworzec", 2);
  Stop szkola = Stop("Szkoła", 3);
  Stop kabel = Stop("Kabel", 4);

  Line line(1, {plac, dworzec, szkola});
  Line line2(2, {kabel, szkola, dworzec});

  lines.push_back(&line);
  lines.push_back(&line2);

  line.setSchedule(ScheduleDay::WORKDAY, Direction::A,
                   {{plac, {"10:00", "10:30"}},
                    {dworzec, {"10:10", "10:40"}},
                    {szkola, {"10:20", "10:50"}}});

  line.setSchedule(ScheduleDay::WORKDAY, Direction::B,
                   {{szkola, {"10:21", "10:51"}},
                    {dworzec, {"10:31", "11:01"}},
                    {plac, {"10:41", "11:11"}}});

  line2.setSchedule(ScheduleDay::WORKDAY, Direction::A,
                    {{kabel, {"10:00", "10:30"}},
                     {szkola, {"10:10", "10:40"}},
                     {dworzec, {"10:20", "10:50"}}});

  line2.setSchedule(ScheduleDay::WORKDAY, Direction::B,
                    {{dworzec, {"10:21", "10:51"}},
                     {szkola, {"10:31", "11:01"}},
                     {kabel, {"10:41", "11:11"}}});

  auto schedule1 = Schedule::getLineScheduleForStop(line, 1);

  for (auto &[day, daySchedule] : schedule1) {
    cout << "Dzień: " << Utils::getScheduleDayName(day) << endl;

    cout << "Kierunek: " << line.getTargetStop(Direction::A) << endl;
    if (daySchedule[Direction::A].empty())
      cout << " Brak rozkładu" << endl;
    else
      for (const auto &time : daySchedule[Direction::A])
        cout << " " << time << endl;

    cout << "Kierunek: " << line.getTargetStop(Direction::B) << endl;
    if (daySchedule[Direction::A].empty())
      cout << " Brak rozkładu" << endl;
    else
      for (const auto &time : daySchedule[Direction::B])
        cout << " " << time << endl;
  }

  auto scheduleAll = Schedule::getAllSchedulesForStop(2, lines);

  for (auto &[line, lineSchedule] : scheduleAll) {
    cout << "Linia: " << line.getNumber() << endl;

    for (auto &[day, daySchedule] : lineSchedule) {
      cout << "Dzień: " << Utils::getScheduleDayName(day) << endl;

      for (auto &[direction, directionSchedule] : daySchedule) {
        cout << "Kierunek: " << line.getTargetStop(direction) << endl;
        if (directionSchedule.empty())
          cout << " Brak rozkładu" << endl;
        else
          for (const auto &time : directionSchedule)
            cout << " " << time << endl;
      }
    }
  }
}
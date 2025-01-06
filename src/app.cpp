#include <iostream>
#include <memory>

#include "app.h"
#include "schedule.h"
#include "stop.h"

using namespace std;

App &App::getInstance() {
  static App instance; // Singleton
  return instance;
}

void App::run() {
  while (true) {
    showMainMenu();
    int choice = getUserInput();
    handleMainMenu(choice);
    if (choice == 4)
      break; // Wyjście
  }
}

App::App() {}

void App::showMainMenu() {
  cout << "\nAGH Municipal System\n";
  cout << "[1] Przystanki\n";
  cout << "[2] Linie\n";
  cout << "[3] Edycja\n";
  cout << "[0] Wyjście\n";
  cout << "Wybierz opcję:\n";
}

int App::getUserInput() {
  cout << "» ";
  int choice;
  cin >> choice;
  return choice;
}

void App::handleMainMenu(int choice) {
  switch (choice) {
  case 1:
    showStopsMenu();
    break;
  case 2:
    showLinesMenu();
    break;
  case 3:
    showEditorMenu();
    break;
  case 0:
    cout << "Do widzenia!\n";
    exit(0);
    break;
  default:
    cout << "Nieprawidłowy wybór!\n";
    break;
  }
}

void App::showStopsMenu() {
  cout << "\n[1] Lista przystanków\n";
  cout << "[2] Wyświetl rozkład przystanku\n";
  cout << "[3] Wyświetl rozkład przystanku dla danej linii\n";
  cout << "[4] Powrót\n";
  int choice = getUserInput();
  handleStopsMenu(choice);
}

void App::showStopsList() {
  cout << "[i] Lista przystanków:\n";
  for (auto &stop : stops) {
    cout << " » [" << stop.getId() << "] " << stop.getName() << endl;
  }
}

void App::setDemoData() {

  stops.push_back(plac);
  stops.push_back(dworzec);
  stops.push_back(szkola);
  stops.push_back(kabel);
  
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
}

void App::showStopSchedule() {
  cout << "Podaj ID przystanku\n";
  int choice = getUserInput();
    auto scheduleAll = Schedule::getAllSchedulesForStop(choice, lines);

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

void App::handleStopsMenu(int choice) {
  switch (choice) {
  case 1:
    showStopsList();
    break;
  case 2: /* Wyświetl rozkład przystanku */
    showStopSchedule();
    break;
  case 3: /* Wyświetl rozkład przystanku dla linii */
    break;
  case 4:
    return; // Powrót do głównego menu
  default:
    cout << "Nieprawidłowy wybór!\n";
    break;
  }
}

void App::showLinesMenu() {
  cout << "\n[1] Lista linii\n";
  cout << "[2] Wyświetl rozkład linii\n";
  cout << "[3] Powrót\n";
  int choice = getUserInput();
  handleLinesMenu(choice);
}

void App::handleLinesMenu(int choice) {
  switch (choice) {
  case 1: /* Wyświetl listę linii */
    break;
  case 2: /* Wyświetl rozkład linii */
    break;
  case 3:
    return; // Powrót do głównego menu
  default:
    cout << "Nieprawidłowy wybór!\n";
    break;
  }
}

void App::showEditorMenu() {
  cout << "\n[1] Edytuj przystanek\n";
  cout << "[2] Edytuj linię\n";
  cout << "[3] Powrót\n";
  int choice = getUserInput();
  handleEditorMenu(choice);
}

void App::handleEditorMenu(int choice) {
  switch (choice) {
  case 1: /* Edytuj przystanek */
    break;
  case 2: /* Edytuj linię */
    break;
  case 3:
    return; // Powrót do głównego menu
  default:
    cout << "Nieprawidłowy wybór!\n";
    break;
  }
}
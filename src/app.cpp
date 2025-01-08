#include <algorithm>
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
  cout << "[2] Lista linii\n";
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
    showLinesList();
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

  lines.push_back(line1);
  lines.push_back(line2);

  line1.setSchedule(ScheduleDay::WORKDAY, Direction::A,
                    {{plac, {"10:00", "10:30"}},
                     {dworzec, {"10:10", "10:40"}},
                     {szkola, {"10:20", "10:50"}}});

  line1.setSchedule(ScheduleDay::WORKDAY, Direction::B,
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

void showLineSchedule(
    const Line &line,
    map<ScheduleDay, map<Direction, vector<string>>> &lineSchedule) {
  cout << "\nLinia: " << line.getNumber() << endl;

  for (auto &[day, daySchedule] : lineSchedule) {
    cout << " Dzień: " << Utils::getScheduleDayName(day) << endl;
    if (daySchedule.empty())
      cout << "   Brak odjazdów" << endl;
    for (auto &[direction, directionSchedule] : daySchedule) {
      cout << "  Kierunek: " << line.getTargetStop(direction).getName() << endl;
      if (directionSchedule.empty())
        cout << "   Brak odjazdów" << endl;
      else
        for (const auto &time : directionSchedule)
          cout << "   " << time << endl;
    }
  }
}

void App::showStopSchedule() {
  cout << "Podaj ID przystanku\n";
  int choice = getUserInput();
  auto scheduleAll = Schedule::getAllSchedulesForStop(choice, lines);

  for (auto &[line, lineSchedule] : scheduleAll) {
    if (lineSchedule.empty())
      continue;
    showLineSchedule(line, lineSchedule);
  }
}

void App::showStopScheduleForLine() {
  cout << "Podaj ID przystanku\n";
  int stopChoice = getUserInput();

  cout << "Podaj numer linii\n";
  int lineChoice = getUserInput();

  try {
    Line targetLine = Line::getLineById(lines, lineChoice);

    auto lineSchedule =
        Schedule::getLineScheduleForStop(targetLine, stopChoice);

    showLineSchedule(targetLine, lineSchedule);
  } catch (const std::runtime_error &e) {
    cout << "Nie ma takiej linii." << endl;
    return;
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
    showStopScheduleForLine();
    break;
  case 4:
    return; // Powrót do głównego menu
  default:
    cout << "Nieprawidłowy wybór!\n";
    break;
  }
}

void App::showLinesList() {
  cout << "[i] Lista linii:\n";
  for (auto &line : lines) {
    cout << " [" << line.getNumber() << "] "
         << line.getTargetStop(Direction::A).getName() << " <-> "
         << line.getTargetStop(Direction::B).getName() << endl;
  }
}

bool handleNextStopAdd() {
  string continueInput =
      Utils::promptInput("Czy chcesz dodać kolejny przystanek? [tak/nie]");
  if (continueInput == "nie")
    return 0;
  else if (continueInput == "tak")
    return 1;
  else
    return handleNextStopAdd();
}

void App::showLineAddMenu() {
  int lineId = Utils::promptNumInput("Podaj numer nowej linii:");

  for (auto &line : lines)
    if (line.getNumber() == lineId) {
      cout << "[!] Linia o takim numerze już istnieje." << endl;
      return;
    }

  vector<Stop> route{};

  cout << "Podaj trasę linii:" << endl;
  uint32_t i = 1;

  while (1) {
    int stopId =
        Utils::promptNumInput("Podaj ID przystanku nr. " + to_string(i));
    try {
      Stop stop = Stop::getStopById(stops, stopId);
      route.push_back(stop);
    } catch (const runtime_error &e) {
      cout << "[!] Nie ma przystanku o takim ID." << endl;
      return;
    }

    if (handleNextStopAdd())
      i++;
    else
      break;
  }

  Line line(lineId, route);
  lines.push_back(line);

  cout << "Dodano linię." << endl;
}

void App::showLineDeleteMenu() {
  int lineId = Utils::promptNumInput("Podaj numer linii, którą chcesz usunąć.");
  handleLineDeleteMenu(lineId);
}

void App::handleLineDeleteMenu(int lineId) {
  try {
    Line targetLine = Line::getLineById(lines, lineId);
    lines.erase(std::remove_if(
                    lines.begin(), lines.end(),
                    [lineId](Line line) { return line.getNumber() == lineId; }),
                lines.end());
    cout << "[i] Linia została usunięta." << endl;
  } catch (const runtime_error &e) {
    cout << "[!] Nie znaleziono linii o podanym numerze." << endl;
  }
}

void App::showLineEditMenu() {
  cout << "\n[1] Utwórz linię\n";
  cout << "[2] Usuń linię\n";
  cout << "[3] Edytuj linię\n";
  cout << "[0] Powrót\n";
  int choice = getUserInput();

  handleLineEditMenu(choice);
}

void App::showTargetLineNumberEditMenu(Line &targetLine) {
  cout << "Podaj nowy numer linii:" << endl;
  int newLineNumber = getUserInput();

  try {
    Line line = Line::getLineById(lines, newLineNumber);
    cout << "[!] Linia z tym numerem już istnieje." << endl;
    return;
  } catch (const runtime_error &e) {
    targetLine.setNumber(newLineNumber);
  }
}

void App::showTargetLineStopDeleteMenu(Line &targetLine) {
  cout << "Podaj ID przystanku, który chcesz usunąć z trasy." << endl;
  int stopId = getUserInput();

  if (!targetLine.hasStop(stopId)) {
    cout << "[!] Ta linia nie ma takiego przystanku na trasie," << endl;
    return;
  }

  Stop stop = Stop::getStopById(stops, stopId);

  auto route = targetLine.getRoute();
  route.erase(std::remove(route.begin(), route.end(), stop), route.end());
  targetLine.setRoute(route);

  auto schedule = targetLine.getSchedule();

  for (auto &[day, daySchedule] : schedule) {
    for (auto &[direction, stopTimes] : daySchedule) {
      stopTimes.erase(stop);
    }
  }

  targetLine.setSchedule(schedule);
}

void App::showTargetLineRoute(Line &targetLine) {
  for (const auto &stop : targetLine.getRoute()) {
    cout << " » [" << stop.getId() << "] " << stop.getName() << endl;
  }
}

void App::showTargetLineStopAddMenu(Line &targetLine) {
  int stopId = Utils::promptNumInput("Podaj ID przystanku:");

  if(targetLine.hasStop(stopId)) {
    cout << "[!] Ta linia ma już ten przystanek na trasie." << endl;
    return;
  }
  try {
    Stop stop = Stop::getStopById(stops, stopId);
    auto route = targetLine.getRoute();
    route.push_back(stop);
    targetLine.setRoute(route);

  } catch (const runtime_error &e) {
    cout << "[!] Nie ma przystanku o takim ID." << endl;
    return;
  }
}

void App::handleTargetLineEditor(int choice, Line &targetLine) {
  switch (choice) {
  case 1:
    showTargetLineRoute(targetLine);
    showTargetLineEditor(targetLine);
    break;
  case 2:
    showTargetLineNumberEditMenu(targetLine);
    showTargetLineEditor(targetLine);
    break;
  case 3:
    showTargetLineStopDeleteMenu(targetLine);
    showTargetLineEditor(targetLine);
    break;
  case 4:
    showTargetLineStopAddMenu(targetLine);
    showTargetLineEditor(targetLine);
    break;
  case 5:
    handleLineDeleteMenu(targetLine.getNumber());
    showLineEditMenu();
    break;
  case 0:
    showLineEditMenu();
    break;
  default:
    cout << "[!] Podaj poprawny numer opcji," << endl;
    showTargetLineEditor(targetLine);
    break;
  }
}

void App::showTargetLineEditor(Line &targetLine) {
  cout << "Edycja: [" << targetLine.getNumber() << "] "
       << targetLine.getTargetStop(Direction::A).getName() << " <-> "
       << targetLine.getTargetStop(Direction::B).getName() << endl;

  cout << "\n[1] Wyświetl całą trasę\n";
  cout << "[2] Zmień numer\n";
  cout << "[3] Usuń przystanek z trasy\n";
  cout << "[4] Dodaj przystanek do trasy\n";
  cout << "[5] Usuń linię\n";
  cout << "[0] Powrót\n";
  int choice = getUserInput();

  handleTargetLineEditor(choice, targetLine);
}

void App::showTargetLineEditMenu() {
  int lineId =
      Utils::promptNumInput("Podaj numer linii, którą chcesz edytować.");

  try {
    Line &targetLine = Line::getLineById(lines, lineId);
    showTargetLineEditor(targetLine);
  } catch (const runtime_error &e) {
    cout << "[!] Nie znaleziono linii o podanym numerze." << endl;
  }
}

void App::handleLineEditMenu(int choice) {
  switch (choice) {
  case 1: /* Utwórz linię */
    showLineAddMenu();
    break;
  case 2: /* Usuń linię */
    showLineDeleteMenu();
    break;
  case 3: /* Edytuj linię */
    showTargetLineEditMenu();
    break;
  case 0:
    return; // Powrót do głównego menu
  default:
    cout << "Nieprawidłowy wybór!\n";
    break;
  }
}

void App::showEditorMenu() {
  cout << "\n[1] Edytuj przystanek\n";
  cout << "[2] Edytuj linie\n";
  cout << "[0] Powrót\n";
  cout << "Wybierz opcję:\n";

  int choice = getUserInput();
  handleEditorMenu(choice);
}

void App::handleEditorMenu(int choice) {
  switch (choice) {
  case 1: /* Edytuj przystanek */
    break;
  case 2: /* Edytuj linię */
    showLineEditMenu();
    break;
  case 0:
    return; // Powrót do głównego menu
  default:
    cout << "Nieprawidłowy wybór!\n";
    break;
  }
}
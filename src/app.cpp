#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "app.h"
#include "schedule.h"
#include "stop.h"
#include "utils.h"

using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::ifstream;
using std::map;
using std::ofstream;
using std::runtime_error;
using std::string;
using std::to_string;
using std::vector;

App &App::getInstance() {
  static App instance;
  return instance;
}

void App::run() { showMainMenu(); }

void App::showMainMenu() {
  adminAuthenticated = 0;

  cout << "\nAGH Municipal Transport System\n";
  cout << "[1] Przystanki\n";
  cout << "[2] Lista linii\n";
  cout << "[3] Edytor\n";
  cout << "[0] Wyjście\n";
  cout << "Wybierz opcję:\n";

  int choice = Utils::getUserInput(0, 3);
  handleMainMenu(choice);
}

void App::handleMainMenu(int choice) {
  switch (choice) {
  case 1:
    showStopsMenu();
    showMainMenu();
    break;
  case 2:
    showLinesList();
    showMainMenu();
    break;
  case 3:
    showEditorMenu();
    showMainMenu();
    break;
  case 0:
    saveData();
    exit(0);
    break;
  default:
    Utils::printErr(ERR_WRONG_CHOICE);
    showMainMenu();
    break;
  }
}

void App::showStopsMenu() {
  cout << "\n[1] Lista przystanków\n";
  cout << "[2] Wyświetl rozkład przystanku\n";
  cout << "[3] Wyświetl rozkład przystanku dla danej linii\n";
  cout << "[0] Powrót\n";
  int choice = Utils::getUserInput(0, 3);
  handleStopsMenu(choice);
}

void App::showStopsList() {
  cout << "[i] Lista przystanków:\n";
  for (auto &stop : stops) {
    cout << " » [" << stop.getId() << "] " << stop.getName() << " ["
         << stop.getTypeString() << "]" << endl;
  }
}

void App::showLineSchedule(
    const Line &line,
    map<ScheduleDay, map<Direction, vector<string>>> &lineSchedule) {
  cout << "\nLinia: " << line.getNumber() << endl;

  for (auto &[day, daySchedule] : lineSchedule) {
    cout << " Dzień: " << Utils::getScheduleDayName(day) << endl;
    if (daySchedule.empty())
      cout << "   Brak odjazdów" << endl;
    for (auto &[direction, directionSchedule] : daySchedule) {
      cout << "  Kierunek: "
           << Stop::getStopById(stops, line.getTargetStop(direction)).getName()
           << endl;
      if (directionSchedule.empty())
        cout << "   Brak odjazdów" << endl;
      else {
        vector<string> sortedSchedule = directionSchedule;
        sort(sortedSchedule.begin(), sortedSchedule.end(),
             [](const string &a, const string &b) {
               return stoi(a.substr(0, 2)) * 60 + stoi(a.substr(3, 2)) <
                      stoi(b.substr(0, 2)) * 60 + stoi(b.substr(3, 2));
             });
        for (const auto &time : sortedSchedule)
          cout << "   " << time << endl;
      }
    }
  }
}

void App::showStopSchedule() {
  cout << "Podaj ID przystanku:" << endl;
  int choice = Utils::getUserInput(MIN_STOP_ID, MAX_STOP_ID);

  if (choice < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  try {
    Stop stop = Stop::getStopById(stops, choice);
  } catch (const runtime_error &e) {
    cout << "[!] Nie znaleziono przystanku o podanym ID." << endl;
    return;
  }

  auto scheduleAll = Schedule::getAllSchedulesForStop(choice, lines);

  for (auto &[line, lineSchedule] : scheduleAll) {
    if (lineSchedule.empty())
      continue;
    showLineSchedule(line, lineSchedule);
  }
}

void App::showStopScheduleForLine() {
  cout << "Podaj ID przystanku" << endl;
  int stopChoice = Utils::getUserInput(MIN_STOP_ID, MAX_STOP_ID);

  if (stopChoice < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  try {
    Stop stop = Stop::getStopById(stops, stopChoice);
  } catch (const runtime_error &e) {
    cout << "[!] Nie znaleziono przystanku o podanym ID." << endl;
    return;
  }

  cout << "Podaj numer linii\n";
  int lineChoice = Utils::getUserInput(MIN_LINE_ID, MAX_LINE_ID);
  if (lineChoice < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  try {
    Line targetLine = Line::getLineById(lines, lineChoice);

    if (!targetLine.hasStop(stopChoice)) {
      Utils::printErr("Ta linia nie ma takiego przystanku na trasie.");
      return;
    }

    auto lineSchedule =
        Schedule::getLineScheduleForStop(targetLine, stopChoice);

    showLineSchedule(targetLine, lineSchedule);
  } catch (const std::runtime_error &e) {
    Utils::printErr(ERR_LINE_NOT_FOUND);
    return;
  }
}

void App::handleStopsMenu(int choice) {
  switch (choice) {
  case 1:
    showStopsList();
    showStopsMenu();
    break;
  case 2:
    showStopSchedule();
    showStopsMenu();
    break;
  case 3:
    showStopScheduleForLine();
    showStopsMenu();
    break;
  case 0:
    showMainMenu();
    break;
  default:
    Utils::printErr(ERR_WRONG_CHOICE);
    showStopsMenu();
    break;
  }
}

void App::showLinesList() {
  cout << "[i] Lista linii:\n";
  for (auto &line : lines) {
    cout << " [" << line.getNumber() << "] "
         << Stop::getStopById(stops, line.getTargetStop(Direction::B)).getName()
         << " <-> "
         << Stop::getStopById(stops, line.getTargetStop(Direction::A)).getName()
         << " [" << line.getTypeString() << "]" << endl;
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
  cout << "Podaj numer nowej linii" << endl;
  int lineId = Utils::getUserInput(MIN_LINE_ID, MAX_LINE_ID);

  if (lineId < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  for (auto &line : lines)
    if (line.getNumber() == lineId) {
      cout << "[!] Linia o takim numerze już istnieje." << endl;
      return;
    }

  cout << "Wybierz typ linii:" << endl;
  cout << "[0] Autobus" << endl;
  cout << "[1] Tramwaj" << endl;
  int lineTypeChoice = Utils::getUserInput(0, 1);

  if (lineTypeChoice < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  TransportType lineType =
      (lineTypeChoice == 0) ? TransportType::BUS : TransportType::TRAM;

  vector<int> route{};

  cout << "Podaj trasę linii:" << endl;
  uint32_t i = 1;

  while (1) {
    cout << "Podaj ID przystanku nr. " + to_string(i) << endl;

    int stopId = Utils::getUserInput(MIN_STOP_ID, MAX_STOP_ID);
    if (stopId < 0) {
      Utils::printErr(ERR_NAN);
      return;
    }

    try {
      Stop stop = Stop::getStopById(stops, stopId);
      if (stop.getType() != lineType) {
        cout << "[!] To jest przystanek typu " << stop.getTypeString() << endl;
        continue;
        ;
      }
      route.push_back(stopId);
    } catch (const runtime_error &e) {
      cout << "[!] Nie ma przystanku o takim ID." << endl;
      return;
    }

    if (handleNextStopAdd())
      i++;
    else
      break;
  }

  Line line(lineId, lineType, route);
  lines.push_back(line);

  cout << "Dodano linię." << endl;
}

void App::showLineDeleteMenu() {
  cout << "Podaj numer linii, którą chcesz usunąć." << endl;
  int lineId = Utils::getUserInput(MIN_LINE_ID, MAX_LINE_ID);
  if (lineId < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

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
    Utils::printErr(ERR_LINE_NOT_FOUND);
  }
}

void App::showLineEditMenu() {
  cout << "Edytor linii\n";
  cout << "\n[1] Utwórz linię\n";
  cout << "[2] Usuń linię\n";
  cout << "[3] Edytuj linię\n";
  cout << "[4] Lista linii\n";
  cout << "[0] Powrót\n";
  int choice = Utils::getUserInput(0, 4);

  handleLineEditMenu(choice);
}

void App::showTargetLineNumberEditMenu(Line &targetLine) {
  cout << "Podaj nowy numer linii:" << endl;
  int newLineNumber = Utils::getUserInput(MIN_LINE_ID, MAX_LINE_ID);

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
  int stopId = Utils::getUserInput(MIN_STOP_ID, MAX_STOP_ID);

  if (stopId < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  if (!targetLine.hasStop(stopId)) {
    cout << "[!] Ta linia nie ma takiego przystanku na trasie," << endl;
    return;
  }

  auto route = targetLine.getRoute();
  route.erase(std::remove(route.begin(), route.end(), stopId), route.end());
  targetLine.setRoute(route);

  auto schedule = targetLine.getSchedule();

  for (auto &[day, daySchedule] : schedule) {
    for (auto &[direction, stopTimes] : daySchedule) {
      stopTimes.erase(stopId);
    }
  }

  targetLine.setSchedule(schedule);
}

void App::showTargetLineRoute(Line &targetLine) {
  for (const auto &stopId : targetLine.getRoute()) {
    cout << " » [" << stopId << "] "
         << Stop::getStopById(stops, stopId).getName() << endl;
  }
}

void App::showTargetLineStopAddMenu(Line &targetLine) {
  cout << "Podaj ID przystanku" << endl;

  int stopId = Utils::getUserInput(MIN_STOP_ID, MAX_STOP_ID);

  if (stopId < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  if (targetLine.hasStop(stopId)) {
    cout << "[!] Ta linia ma już ten przystanek na trasie." << endl;
    return;
  }
  try {
    Stop stop = Stop::getStopById(stops, stopId);

    if (stop.getType() != targetLine.getType()) {
      cout << "[!] To jest przystanek typu " << stop.getTypeString() << endl;
      return;
    }

    auto route = targetLine.getRoute();
    route.push_back(stopId);
    targetLine.setRoute(route);
    cout << "Dodano przystanek do trasy." << endl;
  } catch (const runtime_error &e) {
    Utils::printErr("[!] Nie ma przystanku o takim ID.");
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
  cout << "Edycja linii: [" << targetLine.getNumber() << "] "
       << Stop::getStopById(stops, targetLine.getTargetStop(Direction::B))
              .getName()
       << " <-> "
       << Stop::getStopById(stops, targetLine.getTargetStop(Direction::A))
              .getName()
       << " [" << targetLine.getTypeString() << "]" << endl;

  cout << "\n[1] Wyświetl całą trasę\n";
  cout << "[2] Zmień numer\n";
  cout << "[3] Usuń przystanek z trasy\n";
  cout << "[4] Dodaj przystanek do trasy\n";
  cout << "[5] Usuń linię\n";
  cout << "[0] Powrót\n";
  int choice = Utils::getUserInput(0, 5);

  handleTargetLineEditor(choice, targetLine);
}

void App::showTargetLineEditMenu() {
  cout << "Podaj numer linii, którą chcesz edytować:" << endl;
  int lineId = Utils::getUserInput(MIN_LINE_ID, MAX_LINE_ID);

  if (lineId < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  try {
    Line &targetLine = Line::getLineById(lines, lineId);
    showTargetLineEditor(targetLine);
  } catch (const runtime_error &e) {
    Utils::printErr(ERR_LINE_NOT_FOUND);
  }
}

void App::handleLineEditMenu(int choice) {
  switch (choice) {
  case 1:
    showLineAddMenu();
    showLineEditMenu();
    break;
  case 2:
    showLineDeleteMenu();
    showLineEditMenu();
    break;
  case 3:
    showTargetLineEditMenu();
    showLineEditMenu();
    break;
  case 4:
    showLinesList();
    showLineEditMenu();
    break;
  case 0:
    showEditorMenu();
    break;
  default:
    Utils::printErr(ERR_WRONG_CHOICE);
    break;
  }
}

void App::handleStopDelete(Stop &stop) {
  stops.erase(std::remove(stops.begin(), stops.end(), stop), stops.end());
}

void App::showStopDeleteMenu() {
  cout << "Podaj ID przystanku, który chcesz usunąć:" << endl;

  int choice = Utils::getUserInput(MIN_STOP_ID, MAX_STOP_ID);

  if (choice < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  try {
    Stop stop = Stop::getStopById(stops, choice);

    for (auto &line : lines) {
      if (line.hasStop(choice)) {
        cout << "[!] Nie można usunąć przystanku, ponieważ jest on na trasie "
                "linii "
             << line.getNumber() << "." << endl;
        return;
      }
    }

    handleStopDelete(stop);

    cout << "[i] Przystanek został usunięty." << endl;
  } catch (const runtime_error &e) {
    cout << "[!] Nie znaleziono przystanku o podanym ID." << endl;
  }
}

void App::showStopAddMenu() {
  cout << "Podaj ID nowego przystanku:" << endl;
  int stopId = Utils::getUserInput(MIN_STOP_ID, MAX_STOP_ID);

  if (stopId < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  for (auto &stop : stops) {
    if (stop.getId() == stopId) {
      cout << "[!] Przystanek o takim ID już istnieje." << endl;
      return;
    }
  }

  string stopName = Utils::promptInput("Podaj nazwę nowego przystanku:");

  cout << "Wybierz typ przystanku:" << endl;
  cout << "[0] Autobus" << endl;
  cout << "[1] Tramwaj" << endl;
  int stopTypeChoice = Utils::getUserInput(0, 1);

  if (stopTypeChoice < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  TransportType stopType =
      (stopTypeChoice == 0) ? TransportType::BUS : TransportType::TRAM;

  Stop newStop(stopName, stopId, stopType);
  stops.push_back(newStop);

  cout << "[i] Przystanek został dodany." << endl;
}

void App::handleTargetStopNameChange(Stop &targetStop) {
  string stopName = Utils::promptInput("Podaj nową nazwę przystanku:");

  for (auto &stop : stops) {
    if (stop.getName() == stopName) {
      cout << "[!] Przystanek o takiej nazwie już istnieje." << endl;
      return;
    }
  }

  targetStop.setName(stopName);
}

void App::handleTargetStopIdChange(Stop &targetStop) {
  cout << "Podaj nowe ID przystanku:" << endl;
  int stopId = Utils::getUserInput(MIN_STOP_ID, MAX_STOP_ID);

  if (stopId < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  for (auto &stop : stops) {
    if (stop.getId() == stopId) {
      cout << "[!] Przystanek o takim ID już istnieje." << endl;
      return;
    }
  }

  for (auto &line : lines) {
    auto route = line.getRoute();
    replace(route.begin(), route.end(), targetStop.getId(), stopId);
    line.setRoute(route);

    auto schedule = line.getSchedule();
    for (auto &[day, daySchedule] : schedule) {
      for (auto &[direction, stopTimes] : daySchedule) {
        if (stopTimes.find(targetStop.getId()) != stopTimes.end()) {
          stopTimes[stopId] = stopTimes[targetStop.getId()];
          stopTimes.erase(targetStop.getId());
        }
      }
    }
    line.setSchedule(schedule);
  }

  targetStop.setId(stopId);
}

void App::showTargetStopScheduleEditor(Stop &targetStop, Line &targetLine) {
  cout << "Podaj dzień rozkładu:\n";
  cout << "[0] Dzień roboczy\n";
  cout << "[1] Sobota\n";
  cout << "[2] Święta\n";
  int dayInput = Utils::getUserInput(0, 2);

  ScheduleDay scheduleDay = ScheduleDay::WORKDAY;

  switch (dayInput) {
  case 0:
    break;
  case 1:
    scheduleDay = ScheduleDay::SATURDAY;
    break;
  case 2:
    scheduleDay = ScheduleDay::HOLIDAY;
    break;
  default:
    cout << "[!] Nieprawidłowy dzień tygodnia." << endl;
    return;
  }

  // Check this stuff
  map<Direction, vector<string>> schedule;
  for (auto direction : {Direction::A, Direction::B}) {
    vector<string> times;
    while (true) {
      cout << "Podaj czas odjazdu (HH:MM) dla kierunku "
           << (direction == Direction::A ? "A" : "B") << ": ";
      string time;
      cin >> time;
      if (!Utils::isValidTimeFormat(time)) {
        Utils::printErr("Nieprawidłowy format czasu. Użyj formatu HH:MM.");
        continue;
      } else {
        times.push_back(time);

        cout << "Czy chcesz dodać kolejny czas odjazdu? [tak/nie]: ";
        string continueInput;
        cin >> continueInput;
        if (continueInput == "nie") {
          break;
        }
      }
    }
    schedule[direction] = times;
  }

  targetLine.setSchedule(scheduleDay, Direction::A, targetStop.getId(),
                         schedule[Direction::A]);
  targetLine.setSchedule(scheduleDay, Direction::B, targetStop.getId(),
                         schedule[Direction::B]);

  cout << "[i] Rozkład został zaktualizowany." << endl;
}

void App::showTargetStopScheduleEditMenu(Stop &targetStop) {
  cout << "Podaj numer linii, której chcesz ustalić rozkład dla przystanku: " << endl;
  int lineNumber = Utils::getUserInput(MIN_LINE_ID, MAX_LINE_ID);

  if (lineNumber < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  try {
    Line &line = Line::getLineById(lines, lineNumber);

    if(!line.hasStop(targetStop.getId())) {
      Utils::printErr("Ta linia nie ma takiego przystanku na trasie.");
      return;
    }

    showTargetStopScheduleEditor(targetStop, line);
  } catch (const runtime_error &e) {
    Utils::printErr(ERR_LINE_NOT_FOUND);
  }
}

void App::handleTargetStopEditor(Stop &targetStop, int choice) {
  switch (choice) {
  case 1:
    handleTargetStopNameChange(targetStop);
    showTargetStopEditor(targetStop);
    break;
  case 2:
    handleTargetStopIdChange(targetStop);
    showTargetStopEditor(targetStop);
    break;
  case 3:
    handleStopDelete(targetStop);
    showTargetStopEditor(targetStop);
    break;
  case 4:
    showTargetStopScheduleEditMenu(targetStop);
    showTargetStopEditor(targetStop);
    break;
  case 0:
    showStopEditMenu();
    break;
  default:
    Utils::printErr(ERR_WRONG_CHOICE);
    showTargetStopEditor(targetStop);
    break;
  }
}

void App::showTargetStopEditor(Stop &targetStop) {
  cout << "Edycja przystanku: [" << targetStop.getId() << "] "
       << targetStop.getName() << " [" << targetStop.getTypeString() << "]"
       << endl;

  cout << "[1] Zmień nazwę\n";
  cout << "[2] Zmień ID\n";
  cout << "[3] Usuń przystanek\n";
  cout << "[4] Ustal rozkład linii\n";
  cout << "[0] Powrót\n";
  cout << "Wybierz opcję:\n";

  int choice = Utils::getUserInput(0, 4);
  handleTargetStopEditor(targetStop, choice);
}

void App::showTargetStopEditMenu() {
  cout << "Podaj ID przystanku, który chcesz edytować:" << endl;
  int choice = Utils::getUserInput(MIN_STOP_ID, MAX_STOP_ID);

  if (choice < 0) {
    Utils::printErr(ERR_NAN);
    return;
  }

  try {
    Stop &stop = Stop::getStopById(stops, choice);
    showTargetStopEditor(stop);
  } catch (const runtime_error &e) {
    cout << "[!] Nie znaleziono przystanku o podanym ID." << endl;
  }
}

void App::handleStopEditMenu(int choice) {
  switch (choice) {
  case 1:
    showStopsList();
    showStopEditMenu();
    break;
  case 2:
    showStopAddMenu();
    showStopEditMenu();
    break;
  case 3:
    showStopDeleteMenu();
    showStopEditMenu();
    break;
  case 4:
    showTargetStopEditMenu();
    showStopEditMenu();
    break;
  case 0:
    showEditorMenu();
    break;
  default:
    Utils::printErr(ERR_WRONG_CHOICE);
    showStopEditMenu();
    break;
  }
}

void App::showStopEditMenu() {
  cout << "\n[1] Lista przystanków\n";
  cout << "[2] Dodaj przystanek\n";
  cout << "[3] Usuń przystanek\n";
  cout << "[4] Edytuj przystanek\n";
  cout << "[0] Powrót\n";
  cout << "Wybierz opcję:\n";

  int choice = Utils::getUserInput(0, 4);

  handleStopEditMenu(choice);
}

void App::showEditorMenu() {
  if (!adminAuthenticated) {
    string inputPass = Utils::promptInput("Podaj hasło administratora");

    if (inputPass != adminPassword) {
      Utils::printErr("Nieprawidłowe hasło.");
      return;
    }
    adminAuthenticated = 1;
  }

  cout << "\n[1] Edytor przystanków\n";
  cout << "[2] Edytor linii\n";
  cout << "[3] Ustaw nowe hasło administratora\n";
  cout << "[0] Powrót\n";
  cout << "Wybierz opcję:\n";

  int choice = Utils::getUserInput(0, 3);
  handleEditorMenu(choice);
}

void App::handleEditorMenu(int choice) {
  switch (choice) {
  case 1:
    showStopEditMenu();
    break;
  case 2:
    showLineEditMenu();
    break;
  case 3:
    showAdminPasswordChangeMenu();
    showMainMenu();
    break;
  case 0:
    showMainMenu();
    return;
  default:
    Utils::printErr(ERR_WRONG_CHOICE);
    showEditorMenu();
    break;
  }
}

void App::showAdminPasswordChangeMenu() {
  adminPassword = Utils::promptInput("Podaj nowe hasło:");
  cout << "[i] Hasło zaktualizowano, zaloguj się ponownie." << endl;
  adminAuthenticated = 0;
}

void App::saveData() {
  {
    ofstream ofLines(LINES_DAT_FILE);
    ofstream ofStops(STOPS_DAT_FILE);
    ofstream ofAuth(AUTH_DAT_FILE);

    if (!ofLines.is_open() || !ofStops.is_open() || !ofAuth.is_open()) {
      Utils::printErr("Nie można zapisać pliku wymaganego do działania "
                      "aplikacji. Aplikacja nie zapisała zmian.");
      exit(1);
    }

    boost::archive::text_oarchive arLines(ofLines);
    arLines & lines;

    boost::archive::text_oarchive arStops(ofStops);
    arStops & stops;

    boost::archive::text_oarchive arAuth(ofAuth);
    arAuth & adminPassword;
  }
}

void App::loadData() {
  {
    try {
      ifstream ifLines(LINES_DAT_FILE);
      ifstream ifStops(STOPS_DAT_FILE);
      ifstream ifAuth(AUTH_DAT_FILE);

      if (!ifLines.is_open() || !ifStops.is_open() || !ifAuth.is_open()) {
        Utils::printErr("Pliki konfiguracyjne nie zostały znalezione. Nie "
                        "załadowano żadnych danych.");
        return;
      }

      boost::archive::text_iarchive arLines(ifLines);
      arLines & lines;

      boost::archive::text_iarchive arStops(ifStops);
      arStops & stops;

      boost::archive::text_iarchive arAuth(ifAuth);
      arAuth & adminPassword;
    } catch (const exception &e) {
      Utils::printErr(
          "Wystąpił błąd podczas ładowania danych! Sprawdź poprawność plików");
    }
  }
}
#include <algorithm>
#include <iostream>
#include <memory>

#include "app.h"
#include "schedule.h"
#include "stop.h"

using namespace std;

App &App::getInstance()
{
  static App instance; // Singleton
  return instance;
}

void App::run()
{
  while (true)
  {
    showMainMenu();
    int choice = getUserInput();
    handleMainMenu(choice);
    if (choice == 4)
      break; // Wyjście
  }
}

App::App() {}

void App::showMainMenu()
{
  cout << "\nAGH Municipal System\n";
  cout << "[1] Przystanki\n";
  cout << "[2] Lista linii\n";
  cout << "[3] Edycja\n";
  cout << "[0] Wyjście\n";
  cout << "Wybierz opcję:\n";
}

int App::getUserInput()
{
  cout << "» ";
  int choice;
  cin >> choice;
  return choice;
}

void App::handleMainMenu(int choice)
{
  switch (choice)
  {
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

void App::showStopsMenu()
{
  cout << "\n[1] Lista przystanków\n";
  cout << "[2] Wyświetl rozkład przystanku\n";
  cout << "[3] Wyświetl rozkład przystanku dla danej linii\n";
  cout << "[4] Powrót\n";
  int choice = getUserInput();
  handleStopsMenu(choice);
}

void App::showStopsList()
{
  cout << "[i] Lista przystanków:\n";
  for (auto &stop : stops)
  {
    cout << " » [" << stop.getId() << "] " << stop.getName() << endl;
  }
}

void App::setDemoData()
{

  stops.push_back(plac);
  stops.push_back(dworzec);
  stops.push_back(szkola);
  stops.push_back(kabel);

  lines.push_back(line1);
  lines.push_back(line2);

  line1.setSchedule(ScheduleDay::WORKDAY, Direction::A,
                    {{1, {"10:00", "10:30"}},
                     {2, {"10:10", "10:40"}},
                     {3, {"10:20", "10:50"}}});

  line1.setSchedule(ScheduleDay::WORKDAY, Direction::B,
                    {{1, {"10:21", "10:51"}},
                     {2, {"10:31", "11:01"}},
                     {3, {"10:41", "11:11"}}});

  line2.setSchedule(ScheduleDay::WORKDAY, Direction::A,
                    {{4, {"10:00", "10:30"}},
                     {3, {"10:10", "10:40"}},
                     {2, {"10:20", "10:50"}}});

  line2.setSchedule(ScheduleDay::WORKDAY, Direction::B,
                    {{4, {"10:21", "10:51"}},
                     {3, {"10:31", "11:01"}},
                     {2, {"10:41", "11:11"}}});
}

void App::showLineSchedule(
    const Line &line,
    map<ScheduleDay, map<Direction, vector<string>>> &lineSchedule)
{
  cout << "\nLinia: " << line.getNumber() << endl;

  for (auto &[day, daySchedule] : lineSchedule)
  {
    cout << " Dzień: " << Utils::getScheduleDayName(day) << endl;
    if (daySchedule.empty())
      cout << "   Brak odjazdów" << endl;
    for (auto &[direction, directionSchedule] : daySchedule)
    {
      cout << "  Kierunek: " << Stop::getStopById(stops, line.getTargetStop(direction)).getName() << endl;
      if (directionSchedule.empty())
        cout << "   Brak odjazdów" << endl;
      else
        for (const auto &time : directionSchedule)
          cout << "   " << time << endl;
    }
  }
}

void App::showStopSchedule()
{
  cout << "Podaj ID przystanku\n";
  int choice = getUserInput();
  auto scheduleAll = Schedule::getAllSchedulesForStop(choice, lines);

  for (auto &[line, lineSchedule] : scheduleAll)
  {
    if (lineSchedule.empty())
      continue;
    showLineSchedule(line, lineSchedule);
  }
}

void App::showStopScheduleForLine()
{
  cout << "Podaj ID przystanku\n";
  int stopChoice = getUserInput();

  cout << "Podaj numer linii\n";
  int lineChoice = getUserInput();

  try
  {
    Line targetLine = Line::getLineById(lines, lineChoice);

    auto lineSchedule =
        Schedule::getLineScheduleForStop(targetLine, stopChoice);

    showLineSchedule(targetLine, lineSchedule);
  }
  catch (const std::runtime_error &e)
  {
    cout << "Nie ma takiej linii." << endl;
    return;
  }
}

void App::handleStopsMenu(int choice)
{
  switch (choice)
  {
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
  case 4:
    return; 
  default:
    cout << "Nieprawidłowy wybór!\n";
    break;
  }
}

void App::showLinesList()
{
  cout << "[i] Lista linii:\n";
  for (auto &line : lines)
  {
    cout << " [" << line.getNumber() << "] "
         << Stop::getStopById(stops, line.getTargetStop(Direction::B)).getName() << " <-> "
         << Stop::getStopById(stops, line.getTargetStop(Direction::A)).getName() << endl;
  }
}

bool handleNextStopAdd()
{
  string continueInput =
      Utils::promptInput("Czy chcesz dodać kolejny przystanek? [tak/nie]");
  if (continueInput == "nie")
    return 0;
  else if (continueInput == "tak")
    return 1;
  else
    return handleNextStopAdd();
}

void App::showLineAddMenu()
{
  int lineId = Utils::promptNumInput("Podaj numer nowej linii:");

  for (auto &line : lines)
    if (line.getNumber() == lineId)
    {
      cout << "[!] Linia o takim numerze już istnieje." << endl;
      return;
    }

  vector<int> route{};

  cout << "Podaj trasę linii:" << endl;
  uint32_t i = 1;

  while (1)
  {
    int stopId =
        Utils::promptNumInput("Podaj ID przystanku nr. " + to_string(i));
    try
    {
      Stop stop = Stop::getStopById(stops, stopId);
      route.push_back(stopId);
    }
    catch (const runtime_error &e)
    {
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

void App::showLineDeleteMenu()
{
  int lineId = Utils::promptNumInput("Podaj numer linii, którą chcesz usunąć.");
  handleLineDeleteMenu(lineId);
}

void App::handleLineDeleteMenu(int lineId)
{
  try
  {
    Line targetLine = Line::getLineById(lines, lineId);
    lines.erase(std::remove_if(
                    lines.begin(), lines.end(),
                    [lineId](Line line)
                    { return line.getNumber() == lineId; }),
                lines.end());
    cout << "[i] Linia została usunięta." << endl;
  }
  catch (const runtime_error &e)
  {
    cout << "[!] Nie znaleziono linii o podanym numerze." << endl;
  }
}

void App::showLineEditMenu()
{
  cout << "\n[1] Utwórz linię\n";
  cout << "[2] Usuń linię\n";
  cout << "[3] Edytuj linię\n";
  cout << "[0] Powrót\n";
  int choice = getUserInput();

  handleLineEditMenu(choice);
}

void App::showTargetLineNumberEditMenu(Line &targetLine)
{
  cout << "Podaj nowy numer linii:" << endl;
  int newLineNumber = getUserInput();

  try
  {
    Line line = Line::getLineById(lines, newLineNumber);
    cout << "[!] Linia z tym numerem już istnieje." << endl;
    return;
  }
  catch (const runtime_error &e)
  {
    targetLine.setNumber(newLineNumber);
  }
}

void App::showTargetLineStopDeleteMenu(Line &targetLine)
{
  cout << "Podaj ID przystanku, który chcesz usunąć z trasy." << endl;
  int stopId = getUserInput();

  if (!targetLine.hasStop(stopId))
  {
    cout << "[!] Ta linia nie ma takiego przystanku na trasie," << endl;
    return;
  }

  auto route = targetLine.getRoute();
  route.erase(std::remove(route.begin(), route.end(), stopId), route.end());
  targetLine.setRoute(route);

  auto schedule = targetLine.getSchedule();

  for (auto &[day, daySchedule] : schedule)
  {
    for (auto &[direction, stopTimes] : daySchedule)
    {
      stopTimes.erase(stopId);
    }
  }

  targetLine.setSchedule(schedule);
}

void App::showTargetLineRoute(Line &targetLine)
{
  for (const auto &stopId : targetLine.getRoute())
  {
    cout << " » [" << stopId << "] " << Stop::getStopById(stops, stopId).getName() << endl;
  }
}

void App::showTargetLineStopAddMenu(Line &targetLine)
{
  int stopId = Utils::promptNumInput("Podaj ID przystanku:");

  if (targetLine.hasStop(stopId))
  {
    cout << "[!] Ta linia ma już ten przystanek na trasie." << endl;
    return;
  }
  try
  {
    Stop stop = Stop::getStopById(stops, stopId);
    auto route = targetLine.getRoute();
    route.push_back(stopId);
    targetLine.setRoute(route);
  }
  catch (const runtime_error &e)
  {
    cout << "[!] Nie ma przystanku o takim ID." << endl;
    return;
  }
}

void App::handleTargetLineEditor(int choice, Line &targetLine)
{
  switch (choice)
  {
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

void App::showTargetLineEditor(Line &targetLine)
{
  cout << "Edycja: [" << targetLine.getNumber() << "] "
       << Stop::getStopById(stops, targetLine.getTargetStop(Direction::B)).getName() << " <-> "
       << Stop::getStopById(stops, targetLine.getTargetStop(Direction::A)).getName() << endl;

  cout << "\n[1] Wyświetl całą trasę\n";
  cout << "[2] Zmień numer\n";
  cout << "[3] Usuń przystanek z trasy\n";
  cout << "[4] Dodaj przystanek do trasy\n";
  cout << "[5] Usuń linię\n";
  cout << "[0] Powrót\n";
  int choice = getUserInput();

  handleTargetLineEditor(choice, targetLine);
}

void App::showTargetLineEditMenu()
{
  int lineId =
      Utils::promptNumInput("Podaj numer linii, którą chcesz edytować.");

  try
  {
    Line &targetLine = Line::getLineById(lines, lineId);
    showTargetLineEditor(targetLine);
  }
  catch (const runtime_error &e)
  {
    cout << "[!] Nie znaleziono linii o podanym numerze." << endl;
  }
}

void App::handleLineEditMenu(int choice)
{
  switch (choice)
  {
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
    cout << "[!] Nieprawidłowy wybór!\n";
    break;
  }
}

void App::handleStopDelete(Stop &stop)
{
  stops.erase(std::remove(stops.begin(), stops.end(), stop), stops.end());
}

void App::showStopDeleteMenu()
{
  cout << "Podaj ID przystanku, który chcesz usunąć" << endl;

  int choice = getUserInput();

  try
  {
    Stop stop = Stop::getStopById(stops, choice);

    for (auto &line : lines)
    {
      if (line.hasStop(choice))
      {
        cout << "[!] Nie można usunąć przystanku, ponieważ jest on na trasie linii " << line.getNumber() << "." << endl;
        return;
      }
    }

    handleStopDelete(stop);

    cout << "[i] Przystanek został usunięty." << endl;
  }
  catch (const runtime_error &e)
  {
    cout << "[!] Nie znaleziono przystanku o podanym ID." << endl;
  }
}

void App::showStopAddMenu()
{
  int stopId = Utils::promptNumInput("Podaj ID nowego przystanku:");

  for (auto &stop : stops)
  {
    if (stop.getId() == stopId)
    {
      cout << "[!] Przystanek o takim ID już istnieje." << endl;
      return;
    }
  }

  cin.ignore(); // Ignore the newline character left in the buffer
  string stopName;
  cout << "Podaj nazwę nowego przystanku: ";
  getline(cin, stopName);

  for (auto &stop : stops)
  {
    if (stop.getName() == stopName)
    {
      cout << "[!] Przystanek o takiej nazwie już istnieje." << endl;
      return;
    }
  }

  Stop newStop(stopName, stopId);
  stops.push_back(newStop);

  cout << "[i] Przystanek został dodany." << endl;
}

void App::handleTargetStopNameChange(Stop &targetStop)
{
  cin.ignore(); // Ignore the newline character left in the buffer
  string stopName;
  cout << "Podaj nową nazwę przystanku: ";
  getline(cin, stopName);

  for (auto &stop : stops)
  {
    if (stop.getName() == stopName)
    {
      cout << "[!] Przystanek o takiej nazwie już istnieje." << endl;
      return;
    }
  }

  targetStop.setName(stopName);
}

void App::handleTargetStopIdChange(Stop &targetStop)
{
  int stopId = Utils::promptNumInput("Podaj nowe ID przystanku:");

  for (auto &stop : stops)
  {
    if (stop.getId() == stopId)
    {
      cout << "[!] Przystanek o takim ID już istnieje." << endl;
      return;
    }
  }

  for (auto &line : lines)
  {
    // Update the route
    auto route = line.getRoute();
    replace(route.begin(), route.end(), targetStop.getId(), stopId);
    line.setRoute(route);

    // Update the schedule
    auto schedule = line.getSchedule();
    for (auto &[day, daySchedule] : schedule)
    {
      for (auto &[direction, stopTimes] : daySchedule)
      {
        if (stopTimes.find(targetStop.getId()) != stopTimes.end())
        {
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
  int dayInput = getUserInput();

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



  map<Direction, vector<string>> schedule;
  for (auto direction : {Direction::A, Direction::B}) {
    vector<string> times;
    while (true) {
      cout << "Podaj czas odjazdu (HH:MM) dla kierunku " << (direction == Direction::A ? "A" : "B") << ": ";
      string time;
      cin >> time;
      times.push_back(time);

      cout << "Czy chcesz dodać kolejny czas odjazdu? [tak/nie]: ";
      string continueInput;
      cin >> continueInput;
      if (continueInput == "nie") {
        break;
      }
    }
    schedule[direction] = times;
  }

  targetLine.setSchedule(scheduleDay, Direction::A, targetStop.getId(), schedule[Direction::A]);
  targetLine.setSchedule(scheduleDay, Direction::B, targetStop.getId(), schedule[Direction::B]);

  cout << "[i] Rozkład został zaktualizowany." << endl;
}

void App::showTargetStopScheduleEditMenu(Stop &targetStop) {
  cout << "Podaj numer linii, którą chcesz ustalić rozkład dla przystanku: ";
  int lineNumber = getUserInput();

  try
  {
    Line &line = Line::getLineById(lines, lineNumber);
    showTargetStopScheduleEditor(targetStop, line);
  }
  catch (const runtime_error &e)
  {
    cout << "[!] Nie znaleziono linii o podanym numerze." << endl;
  }
}

void App::handleTargetStopEditor(Stop &targetStop, int choice)
{
  switch (choice)
  {
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
    cout << "[!] Nieprawidłowy wybór!\n";
    showTargetStopEditor(targetStop);
    break;
  }
}

void App::showTargetStopEditor(Stop &targetStop)
{
  cout << "Edycja przystanku: [" << targetStop.getId() << "] " << targetStop.getName() << endl;

  cout << "[1] Zmień nazwę\n";
  cout << "[2] Zmień ID\n";
  cout << "[3] Usuń przystanek\n";
  cout << "[4] Ustal rozkład linii\n";
  cout << "[0] Powrót\n";
  cout << "Wybierz opcję:\n";

  int choice = getUserInput();
  handleTargetStopEditor(targetStop, choice);
}

void App::showTargetStopEditMenu()
{
  cout << "Podaj ID przystanku, który chcesz edytować" << endl;
  int choice = getUserInput();

  try
  {
    Stop &stop = Stop::getStopById(stops, choice);
    showTargetStopEditor(stop);
  }
  catch (const runtime_error &e)
  {
    cout << "[!] Nie znaleziono przystanku o podanym ID." << endl;
  }
}

void App::handleStopEditMenu(int choice)
{
  switch (choice)
  {
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
    cout << "[!] Nieprawidłowy wybór!\n";
    showStopEditMenu();
    break;
  }
}

void App::showStopEditMenu()
{
  cout << "\n[1] Lista przystanków\n";
  cout << "[2] Dodaj przystanek\n";
  cout << "[3] Usuń przystanek\n";
  cout << "[4] Edytuj przystanek\n";
  cout << "[0] Powrót\n";
  cout << "Wybierz opcję:\n";

  int choice = getUserInput();

  handleStopEditMenu(choice);
}

void App::showEditorMenu()
{
  cout << "\n[1] Edytuj przystanek\n";
  cout << "[2] Edytuj linie\n";
  cout << "[0] Powrót\n";
  cout << "Wybierz opcję:\n";

  int choice = getUserInput();
  handleEditorMenu(choice);
}

void App::handleEditorMenu(int choice)
{
  switch (choice)
  {
  case 1: /* Edytuj przystanek */
    showStopEditMenu();
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
#pragma once

#include <vector>

#include "stop.h"
#include "line.h"

using namespace std;

class App {
public:
  static App &getInstance();

  void run();

  void setDemoData();

private:
  App();
  App(const App &) = delete;
  App &operator=(const App &) = delete;

  vector<Line> lines;
  vector<Stop> stops;

  Stop plac = Stop("Plac Centralny", 1);
  Stop dworzec = Stop("Dworzec", 2);
  Stop szkola = Stop("Szkoła", 3);
  Stop kabel = Stop("Kabel", 4);

  Line line1 = Line(1, {plac, dworzec, szkola});
  Line line2 = Line(2, {kabel, szkola, dworzec});

  void showMainMenu();

  int getUserInput();

  void handleMainMenu(int choice);

  void showStopsMenu();

  void handleStopsMenu(int choice);

  void showEditorMenu();

  void handleEditorMenu(int choice);

  void showLineEditMenu();

  void handleLineEditMenu(int choice);

  void showLineAddMenu();

  void showLineDeleteMenu();

  void handleLineDeleteMenu(int lineId);

  void showTargetLineEditMenu();

  void showTargetLineEditor(Line &targetLine);

  void handleTargetLineEditor(int choice, Line &targetLine);

  void showTargetLineNumberEditMenu(Line &targetLine);

  void showTargetLineStopDeleteMenu(Line &targetLine);

  void showTargetLineStopAddMenu(Line &targetLine);

  void showTargetLineRoute(Line &targetLine);

  void showStopsList();
  void showStopSchedule();
  void showStopScheduleForLine();
  void showLinesList();
};
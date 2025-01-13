#ifndef APP_H
#define APP_H

#include <map>
#include <string>
#include <vector>

#include "line.h"
#include "stop.h"
#include "enums.h"

using std::map;
using std::string;
using std::vector;

/**
 * @class App
 * @brief Singleton class that manages the municipal transport application.
 * 
 * The App class provides public methods to run the application, save and load data,
 * and private methods handling various menus and operations related to lines and stops.
 */
class App {
public:
  /**
   * @brief Get the singleton instance of the App class.
   * @return Reference to the singleton instance of the App class.
   */
  static App &getInstance();

  /**
   * @brief Run the application.
   */
  void run();

  /**
   * @brief Save the application data to a file.
   */
  void saveData();

  /**
   * @brief Load the application data from a file.
   */
  void loadData();

private:

  vector<Line> lines;
  vector<Stop> stops;
  string adminPassword = "admin";
  bool adminAuthenticated = 0;

  /**
   * @brief Default constructor.
   */
  App() = default;

  /**
   * @brief Deleted copy constructor to enforce singleton pattern.
   */
  App(const App &) = delete;

  /**
   * @brief Deleted assignment operator to enforce singleton pattern.
   */
  App &operator=(const App &) = delete;

  /**
   * @brief Show the main menu of the application.
   */
  void showMainMenu();

  /**
   * @brief Handle the user's choice in the main menu.
   * @param choice The user's choice.
   */
  void handleMainMenu(int choice);

  /**
   * @brief Show the schedule for a specific line.
   * @param line The line for which to show the schedule.
   * @param lineSchedule The schedule data for the line.
   */
  void showLineSchedule(const Line &line, map<ScheduleDay, map<Direction, vector<string>>> &lineSchedule);

  /**
   * @brief Show the stops menu.
   */
  void showStopsMenu();

  /**
   * @brief Handle the user's choice in the stops menu.
   * @param choice The user's choice.
   */
  void handleStopsMenu(int choice);

  /**
   * @brief Show the editor menu.
   */
  void showEditorMenu();

  /**
   * @brief Handle the user's choice in the editor menu.
   * @param choice The user's choice.
   */
  void handleEditorMenu(int choice);

  /**
   * @brief Show the line edit menu.
   */
  void showLineEditMenu();

  /**
   * @brief Handle the user's choice in the line edit menu.
   * @param choice The user's choice.
   */
  void handleLineEditMenu(int choice);

  /**
   * @brief Show the line add menu.
   */
  void showLineAddMenu();

  /**
   * @brief Show the line delete menu.
   */
  void showLineDeleteMenu();

  /**
   * @brief Handle the user's choice in the line delete menu.
   * @param lineId The ID of the line to delete.
   */
  void handleLineDeleteMenu(int lineId);

  /**
   * @brief Show the target line edit menu.
   */
  void showTargetLineEditMenu();

  /**
   * @brief Show the editor for a specific line.
   * @param targetLine The line to edit.
   */
  void showTargetLineEditor(Line &targetLine);

  /**
   * @brief Handle the user's choice in the target line editor.
   * @param choice The user's choice.
   * @param targetLine The line to edit.
   */
  void handleTargetLineEditor(int choice, Line &targetLine);

  /**
   * @brief Show the menu to edit the number of a specific line.
   * @param targetLine The line to edit.
   */
  void showTargetLineNumberEditMenu(Line &targetLine);

  /**
   * @brief Show the menu to delete a stop from a specific line.
   * @param targetLine The line to edit.
   */
  void showTargetLineStopDeleteMenu(Line &targetLine);

  /**
   * @brief Show the menu to add a stop to a specific line.
   * @param targetLine The line to edit.
   */
  void showTargetLineStopAddMenu(Line &targetLine);

  /**
   * @brief Show the route of a specific line.
   * @param targetLine The line to show the route for.
   */
  void showTargetLineRoute(Line &targetLine);

  /**
   * @brief Handle the user's choice in the stop edit menu.
   * @param choice The user's choice.
   */
  void handleStopEditMenu(int choice);

  /**
   * @brief Show the stop edit menu.
   */
  void showStopEditMenu();

  /**
   * @brief Handle the deletion of a specific stop.
   * @param stop The stop to delete.
   */
  void handleStopDelete(Stop &stop);

  /**
   * @brief Show the stop delete menu.
   */
  void showStopDeleteMenu();

  /**
   * @brief Show the stop add menu.
   */
  void showStopAddMenu();

  /**
   * @brief Show the target stop edit menu.
   */
  void showTargetStopEditMenu();

  /**
   * @brief Show the editor for a specific stop.
   * @param targetStop The stop to edit.
   */
  void showTargetStopEditor(Stop &targetStop);

  /**
   * @brief Handle the user's choice in the target stop editor.
   * @param targetStop The stop to edit.
   * @param choice The user's choice.
   */
  void handleTargetStopEditor(Stop &targetStop, int choice);

  /**
   * @brief Handle the name change of a specific stop.
   * @param targetStop The stop to edit.
   */
  void handleTargetStopNameChange(Stop &targetStop);

  /**
   * @brief Handle the ID change of a specific stop.
   * @param targetStop The stop to edit.
   */
  void handleTargetStopIdChange(Stop &targetStop);

  /**
   * @brief Show the menu to edit the schedule of a specific stop.
   * @param targetStop The stop to edit.
   */
  void showTargetStopScheduleEditMenu(Stop &targetStop);

  /**
   * @brief Show the editor for the schedule of a specific stop.
   * @param targetStop The stop to edit.
   * @param targetLine The line associated with the stop.
   */
  void showTargetStopScheduleEditor(Stop &targetStop, Line &targetLine);

  /**
   * @brief Show the list of stops.
   */
  void showStopsList();

  /**
   * @brief Show the schedule of a specific stop.
   */
  void showStopSchedule();

  /**
   * @brief Show the schedule of a specific stop for a specific line.
   */
  void showStopScheduleForLine();

  /**
   * @brief Show the list of lines.
   */
  void showLinesList();

  /**
   * @brief Show the menu to change the admin password.
   */
  void showAdminPasswordChangeMenu();

  /**
   * @brief Show the connection finder.
   */
  void showConnectionFinder();
};

#endif // APP_H
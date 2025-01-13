#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <string>

#include "enums.h"

using std::map;
using std::string;

// Min/max values for line number and stop id
#define MIN_LINE_ID 0
#define MAX_LINE_ID 2147483647

#define MIN_STOP_ID 1
#define MAX_STOP_ID 2147483647

// Definitions of frequently used strings
#define ERR_WRONG_CHOICE "Nieprawidłowy wybór!"
#define ERR_NAN "Podana wartość musi być poprawną liczbą."
#define ERR_LINE_NOT_FOUND "Nie znaleziono linii o podanym numerze."

// Storage file locations
#define LINES_DAT_FILE "../lines.dat"
#define STOPS_DAT_FILE "../stops.dat"
#define AUTH_DAT_FILE "../auth.dat"

/**
 * @class Utils
 * @brief Utility class providing various helper functions.
 */
class Utils {
public:
  /**
   * @brief Returns the name of the schedule day as a string.
   * @param day The schedule day to convert.
   * @return The name of the schedule day as a string.
   */
  static string getScheduleDayName(ScheduleDay day);

  /**
   * @brief Displays a selection input prompt with a map of possible options.
   * @param promptMap A map containing the possible options to select.
   * @return The selected input number.
   */
  static int promptSel(const map<int, string> promptMap);

  /**
   * @brief Displays an input prompt using a string as the prompt text.
   * @param promptText The text to display as the prompt.
   * @return The input string from the user.
   */
  static string promptInput(const string promptText);

  /**
   * @brief Prints an error message.
   * @param errText The error message to print.
   */
  static void printErr(const string errText);

  /**
   * @brief Validates if a string can be parsed as an integer.
   * @param input The string to validate.
   * @return True if the string can be parsed as an integer, false otherwise.
   */
  static bool validateInt(const string &input);

  /**
   * @brief Gets user numeric input with proper validation.
   * @param min The minimum valid input value.
   * @param max The maximum valid input value.
   * @return The user input or -1 as an error value.
   */
  static int getUserInput(int min, int max);

  /**
   * @brief Checks if a string can be validated as a time in HH:MM format.
   * @param time The string to validate.
   * @return True if the string is in valid HH:MM format, false otherwise.
   */
  static bool isValidTimeFormat(const string &time);
};

#endif // UTILS_H
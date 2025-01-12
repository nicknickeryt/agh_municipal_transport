#pragma once

#include <string>
#include <map>

using namespace std;

enum class Direction { A, B };
enum class ScheduleDay { WORKDAY, SATURDAY, HOLIDAY };

#define MIN_LINE_ID 0
#define MAX_LINE_ID 2147483647

#define MIN_STOP_ID 1
#define MAX_STOP_ID 2147483647

#define ERR_WRONG_CHOICE "Nieprawidłowy wybór!"
#define ERR_NAN "Podana wartość musi być poprawną liczbą."
#define ERR_LINE_NOT_FOUND "Nie znaleziono linii o podanym numerze."

class Utils {
public:
  static string getScheduleDayName(ScheduleDay day);

// Shows the selection input and returns it
    // Returns the input number
    static int promptSel();

    // Shows the selection input and displays a prompt map containing the possible options to select
    // Returns the input number
    static int promptSel(const map<int, string> promptMap);

    // Shows the input prompt
    // Returns the input string
    static string promptInput();

    // Shows the input prompt using a string as a prompt text
    // Returns the input string
    static string promptInput(const string promptText);

    // Shows the input prompt using a string as a prompt text
    // Returns the input number
    static int promptNumInput(const string promptText);

    // Prints the error using string
    static void printErr(const string errText);

    // Validates if a string can be parsed as an int
    static bool validateInt(const string &input);

    static int getUserInput(int min, int max);
};
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <regex>

#include "utils.h"

using std::string;
using std::map;
using std::cin;
using std::cout;
using std::endl;
using std::invalid_argument;

int Utils::getUserInput(int min, int max) {
  cout << "» ";

  string input;
  cin >> input;

  if(!validateInt(input)) return -1;
  
  int choice = stoi(input);
  return (choice >= min && choice <= max) ? choice : -1;
}


string Utils::getScheduleDayName(ScheduleDay day) {
  switch (day) {
  case ScheduleDay::WORKDAY:
    return "Dzień roboczy";
  case ScheduleDay::SATURDAY:
    return "Sobota";
  case ScheduleDay::HOLIDAY:
    return "Święto";
  default:
    throw invalid_argument("Invalid ScheduleDay");
  }
}

int Utils::promptSel(const map<int, string> promptMap) {
    for (auto x : promptMap) {
        cout << " [" << x.first << "] " << x.second << endl;
    }

    int ret;

    string input{};

    while (1) {
        cout << "» ";
        cin >> input;
        if (validateInt(input)) {
            std::istringstream(input) >> ret;
            break;
        }
        printErr(ERR_NAN);
    }
    return ret;
}

bool Utils::validateInt(const std::string &input) {
    std::istringstream iss(input);
    int value;
    return (iss >> value) && (iss.eof());
}

string Utils::promptInput(const string promptText) {

    cout << promptText << endl;

    string ret{};
    cout << "» ";

    cin.ignore();
    getline(cin, ret);
    return ret;
}

void Utils::printErr(const string errText) { cout << "[!] " << errText << endl; }

bool Utils::isValidTimeFormat(const std::string& time) {
    std::regex timeFormat(R"(^([01]\d|2[0-3]):([0-5]\d)$)");
    return std::regex_match(time, timeFormat);
  }
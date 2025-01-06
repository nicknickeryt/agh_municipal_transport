#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <map>

#include "utils.h"

using namespace std;

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

int Utils::promptSel() {
    int ret;

    string input{};

    while (1) {
        cout << "» ";
        cin >> input;
        if (validateInt(input)) {
            std::istringstream(input) >> ret;
            break;
        }
        printErr("ERR_NAN");
    }
    return ret;
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
        printErr("ERR_NAN");
    }
    return ret;
}

bool Utils::validateInt(const std::string &input) {
    std::istringstream iss(input);
    int value;
    return (iss >> value) && (iss.eof());
}

string Utils::promptInput() {
    string ret{};
    cout << "» ";
    cin >> ret;
    return ret;
}

string Utils::promptInput(const string promptText) {
    cout << promptText << endl;

    string ret{};
    cout << "» ";
    cin >> ret;
    return ret;
}

int Utils::promptNumInput(const string promptText) {
    cout << promptText << endl;

    int ret{};
    cout << "» ";
    cin >> ret;
    return ret;
}

void Utils::printErr(const string errText) { cout << "[ ! ] " << errText << endl; }
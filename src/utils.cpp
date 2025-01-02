#include "utils.h"

#include <iostream>
#include <sstream>

using std::cin, std::cout, std::endl, std::map, std::string;    

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
        printErr("Nieprawidłowa liczba.");
    }
    return ret;
}

void Utils::printErr(const string errText) { cout << "[ ! ] " << errText << endl; }

bool Utils::validateInt(const std::string &input) {
    std::istringstream iss(input);
    int value;
    return (iss >> value) && (iss.eof());
}
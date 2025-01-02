#pragma once

#include <map>
#include <string>
using std::map, std::string;

class Utils
{
public:
    static int promptSel(const map<int, string> promptMap);
    static void printErr(const string errText);
    static bool validateInt(const string &input);
};
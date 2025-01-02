#include "stop.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

Stop::Stop(string name, int id)
    : stopName(name), stopId(id) {}

string Stop::getName() const {
    return stopName;
}

int Stop::getId() const {
    return stopId;
}

void Stop::printInfo(){
    cout << "Stop Name: " << stopName << endl;
    cout << "Stop ID: " << stopId << endl;
}
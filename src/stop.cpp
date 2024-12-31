#include "stop.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

Stop::Stop(string name, int id, int scheduleId)
    : stopName(name), stopId(id), stopScheduleId(scheduleId) {}

string Stop::getName() const {
    return stopName;
}

int Stop::getId() const {
    return stopId;
}

int Stop::getScheduleId() const {
    return stopScheduleId;
}

void Stop::printInfo(){
    cout << "Stop Name: " << stopName << endl;
    cout << "Stop ID: " << stopId << endl;
    cout << "Schedule ID: " << stopScheduleId << endl;
}
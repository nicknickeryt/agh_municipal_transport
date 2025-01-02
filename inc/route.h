#pragma once

#include <vector>
#include <string>
#include <map>

#include "stop.h"
#include "vehicle.h"

using std::string, std::vector, std::map, std::pair;

class Route {
private:
    map<Stop, string> routeStopArrivals;
    Vehicle routeVehicle;

public:
    Route(map<Stop, string> stopArrivals, Vehicle vehicle);

    void addStop(Stop stop, string arrivalTime);
    vector<Stop> getStops();
    map<Stop, string> getStopArrivals();
    vector<pair<Stop, string>> getSortedStopArrivals();
    Vehicle getVehicle();
    void printInfo(); 

};

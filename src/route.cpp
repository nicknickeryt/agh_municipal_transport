#include "route.h"
#include "stop.h"
#include "vehicle.h"

#include <iostream>
#include <algorithm>

using std::cout, std::endl, std::string, std::vector, std::map, std::pair;

Route::Route(map<Stop, string> stopArrivals, Vehicle vehicle) : routeStopArrivals(stopArrivals), routeVehicle(vehicle) {}

void Route::addStop(Stop stop, string arrivalTime)
{
    routeStopArrivals[stop] = arrivalTime;
}

vector<Stop> Route::getStops()
{
    vector<Stop> stops;
    for (auto const &pair : routeStopArrivals)
    {
        stops.push_back(pair.first);
    }
    return stops;
}

map<Stop, string> Route::getStopArrivals()
{
    return routeStopArrivals;
}

Vehicle Route::getVehicle()
{
    return routeVehicle;
}

vector<pair<Stop, string>> Route::getSortedStopArrivals()
{
    vector<pair<Stop, string>> sortedStopArrivals(routeStopArrivals.begin(), routeStopArrivals.end());
    std::sort(sortedStopArrivals.begin(), sortedStopArrivals.end(), [](const pair<Stop, string> &a, const pair<Stop, string> &b) {
        return a.second < b.second;
    });
    return sortedStopArrivals;
}

void Route::printInfo()
{
    cout << "Route info:" << endl;
    cout << "  Vehicle: " << routeVehicle.getModel() << " (" << routeVehicle.getTypeString() << ")" << endl;
    auto sortedStopArrivals = getSortedStopArrivals();
    for (auto const &pair : sortedStopArrivals)
    {
        cout << "   " << pair.first.getName() << ": " << pair.second << endl;
    }
}
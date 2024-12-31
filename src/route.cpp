#include "route.h"
#include "stop.h"
#include "vehicle.h"

#include <iostream>

using std::cout, std::endl, std::string, std::vector, std::map;

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

void Route::printInfo()
{
    cout << "Route info:" << endl;
    cout << "  Vehicle: " << routeVehicle.getModel() << " (" << routeVehicle.getTypeString() << ")" << endl;
    for (auto const &pair : routeStopArrivals)
    {
        cout << "   " << pair.first.getName() << ": " << pair.second << endl;
    }
}
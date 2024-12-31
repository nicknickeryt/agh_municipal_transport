#include "vehicle.h"
#include "stop.h"
#include "route.h"
#include "line.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

using std::string, std::vector, std::map, std::cout, std::endl;

int main() {
    Vehicle vehicle(1, BUS, "Jelcz PR110", 1983, 2, 2);
    vehicle.printInfo();

    Vehicle vehicle1(2, BUS, "Autosan H9", 1979, 2, 2);
    vehicle1.printInfo();
    
    Stop placCentralny("Plac Centralny", 1, 1);
    Stop rondoMogilskie("Rondo Mogilskie", 2, 2);
    Stop dworzecGlowny("Dworzec Glowny", 3, 3);

    placCentralny.printInfo();
    rondoMogilskie.printInfo();
    dworzecGlowny.printInfo();

    map<Stop, string> stopArrivals1 = {
        {placCentralny, "08:00"},
        {rondoMogilskie, "08:15"},
        {dworzecGlowny, "08:30"}
    };

    Route route1(stopArrivals1, vehicle);
    route1.printInfo();

    map<Stop, string> stopArrivals2 = {
        {placCentralny, "09:00"},
        {rondoMogilskie, "09:15"},
        {dworzecGlowny, "09:30"}
    };

    Route route2(stopArrivals2, vehicle1);
    route2.printInfo();

    vector<Route> routes = {route1, route2};
    Line line(193, routes);
    line.addRoute(route1);
    line.addRoute(route2);
    
    cout << "Line " <<line.getLineNumber() << endl;
    cout << "Routes for it: " << endl;
    for (auto &route : line.getRoutes()) route.printInfo();
    
    return 0;
}
#pragma once

#include <vector>

#include "route.h"
#include "line.h"
#include "vehicle.h"
#include "stop.h"

// TODO proper singleton

using std::vector;

class App
{
private:

    Vehicle jelcz = Vehicle(0, BUS, "Jelcz PR110", 1983);
    Vehicle autosan = Vehicle(1, BUS, "Autosan H9", 1997);

    Stop plac = Stop("Plac Centralny", 0);
    Stop dworzec = Stop("Dworzec główny", 1);
    Stop kabel = Stop("Kabel", 2);

    Route route1 = Route({{plac, "8:00",}, {dworzec, "8:20"}}, jelcz);
    Route route2 = Route({{plac, "8:15",}, {dworzec, "8:35"}}, autosan);

    Route route3 = Route({{plac, "10:00",}, {kabel, "10:20"}, {dworzec, "10:30"}}, jelcz);
    Route route4 = Route({{plac, "10:15",}, {kabel, "10:35"}, {dworzec, "10:45"}}, autosan);
    Route route5 = Route({{dworzec, "10:50",}, {kabel, "11:00"}, {plac, "11:20"}}, autosan);

    Line line193 = Line(193, {route1, route2});
    Line line139 = Line(139, {route3, route4, route5});

    vector<Vehicle> vehicles = vector<Vehicle>{jelcz, autosan};
    vector<Line> lines = vector<Line>{line193, line139};
    vector<Route> routes = vector<Route>{route1, route2, route3, route4, route5};

public:
    App();

    void launch();

    void launchEditMenu();
    void launchEditVehicleMenu();
    void launchAddNewVehicle();
    void launchEditVehicle();

    void launchLinesMenu();
    void launchLinesDetailsMenu();
    void launchLineDetailsMenu(Line &line);
    void launchLineStopsMenu(Line& line);

    void printLines();

    void printVehicles();
};
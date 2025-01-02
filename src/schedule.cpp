#include "schedule.h"
#include <iostream>

using std::cout, std::endl, std::string;

void Schedule::printScheduleForStop(const Stop& stop, const std::vector<Line>& lines) {
    for (const auto& line : lines) 
        printScheduleForStop(stop, line);
}

void Schedule::printScheduleForStop(const Stop& stop, const Line& line) {

        cout << " Linia " << line.getLineNumber() << ":" << endl;
        for (auto route : line.getRoutes()) {
            try {
                string arrivalTime = route.getStopArrivals()[stop];
                vector<pair<Stop, string>> stops = route.getSortedStopArrivals();
                cout << "  " << arrivalTime  << " [" << stops[0].first.getName() << " -> " << stops[stops.size() - 1].first.getName() << "]" << endl;
            } catch (const std::out_of_range&) {
                // Stop not found in this route, continue to the next route
            }
        }
}
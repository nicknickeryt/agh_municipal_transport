#pragma once 

#include <string>
#include <vector>

using std::string;

class Stop
{
private:
    std::string stopName;
    int stopId;
    int stopScheduleId; // New member variable
public:
    Stop(string name, int id, int scheduleId);

    string getName() const;
    int getId() const;
    int getScheduleId() const; // New method to get scheduleId
    void printInfo();    // New method to print information

    // this is required for using Stop as a key in a map lolz
    bool operator<(const Stop& other) const {
        return stopId < other.stopId;
    }
};
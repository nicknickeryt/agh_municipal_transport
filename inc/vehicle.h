#pragma once 

#include <string>

using std::string; 

enum VehicleType
{
    BUS,
    TRAM,
    TROLLEYBUS
};

class Vehicle {
    int vehicleId;
    VehicleType vehicleType;
    string vehicleModel;
    int vehicleProdYear;
    int vehicleCurrentLine;
    int vehicleCurrentRouteID; // change to Route

public:
    Vehicle(int id, VehicleType type, string model, int prodYear, int currentLine, int currentRouteID);

    void setID(int id);
    void setCurrentLine(int id);
    void setCurrentRouteID(int id);

    int getID();
    VehicleType getType();
    string getTypeString();
    string getModel();
    int getProdYear();
    int getCurrentLine();
    int getCurrentRouteID();

    void printInfo();
};
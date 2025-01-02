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

public:
    Vehicle(int id, VehicleType type, string model, int prodYear);

    int getID();
    VehicleType getType();
    string getTypeString();
    string getModel();
    int getProdYear();

    void setType(VehicleType type);
    void setModel(string model);
    void setProdYear(int year);

    void printInfo();
};
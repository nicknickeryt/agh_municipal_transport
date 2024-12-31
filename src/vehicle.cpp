#include "vehicle.h"
#include <iostream>

using std::cout;
using std::endl;


Vehicle::Vehicle(int id, VehicleType type, string model, int prodYear, int currentLine, int currentRouteID) : vehicleId(id),
                                                                                                         vehicleType(type),
                                                                                                         vehicleModel(model),
                                                                                                         vehicleProdYear(prodYear),
                                                                                                         vehicleCurrentLine(currentLine),
                                                                                                         vehicleCurrentRouteID(currentRouteID)
{
}

void Vehicle::setID(int id)
{
    vehicleId = id;
}
void Vehicle::setCurrentLine(int line)
{
    vehicleCurrentLine = line;
}
void Vehicle::setCurrentRouteID(int id)
{
    vehicleCurrentRouteID = id;
}

int Vehicle::getID()
{
    return vehicleId;
}

VehicleType Vehicle::getType()
{
    return vehicleType;
}

string Vehicle::getTypeString(){
    switch (vehicleType)
    {
    case BUS:
        return "Bus";
        break;
    case TRAM:
        return "Tram";
        break;
    case TROLLEYBUS:
        return "Trolleybus";
        break;
    default:
        return "Unknown";
        break;
    }
}

std::string Vehicle::getModel()
{
    return vehicleModel;
}

int Vehicle::getProdYear()
{
    return vehicleProdYear;
}

int Vehicle::getCurrentLine()
{
    return vehicleCurrentLine;
}

int Vehicle::getCurrentRouteID()
{
    return vehicleCurrentRouteID;
}

void Vehicle::printInfo() {
    cout << "Vehicle ID: " << vehicleId << endl;
    cout << "Type: " << getTypeString() << endl;
    cout << "Model: " << vehicleModel << endl;
    cout << "Production Year: " << vehicleProdYear << endl;
    cout << "Current Line: " << vehicleCurrentLine << endl;
    cout << "Current Route ID: " << vehicleCurrentRouteID << endl;
}
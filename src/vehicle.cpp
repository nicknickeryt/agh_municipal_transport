#include "vehicle.h"
#include <iostream>

using std::cout;
using std::endl;

Vehicle::Vehicle(int id, VehicleType type, string model, int prodYear) : vehicleId(id),
                                                                         vehicleType(type),
                                                                         vehicleModel(model),
                                                                         vehicleProdYear(prodYear)
{
}

int Vehicle::getID()
{
    return vehicleId;
}

VehicleType Vehicle::getType()
{
    return vehicleType;
}

string Vehicle::getTypeString()
{
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

void Vehicle::setType(VehicleType type)
{
    vehicleType = type;
}
void Vehicle::setModel(string model)
{
    vehicleModel = model;
}
void Vehicle::setProdYear(int year)
{
    vehicleProdYear = year;
}

void Vehicle::printInfo()
{
    cout << "Vehicle ID: " << vehicleId << endl;
    cout << "Type: " << getTypeString() << endl;
    cout << "Model: " << vehicleModel << endl;
    cout << "Production Year: " << vehicleProdYear << endl;
}
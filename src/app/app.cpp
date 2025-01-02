#include "app/app.h"
#include "utils.h"
#include "schedule.h"

#include <iostream>
#include <string>
#include <cctype>
#include <set>
#include <stdint.h>

using std::cout, std::endl, std::string, std::getline, std::cin, std::stoi;

App::App() {}

bool isNumber(const string &str)
{
    for (char const &c : str)
    {
        if (isdigit(c) == 0)
            return false;
    }
    return true;
}

int getChoiceInt(string editChoiceStr)
{
    return isNumber(editChoiceStr) ? stoi(editChoiceStr) : -1;
}

void App::launch()
{
    cout << "Witaj w AGH Municipal Transport" << endl;
    cout << "Wybierz opcje: " << endl;

    int choice = Utils::promptSel({{1, "Edycja"},
                                   {2, "Linie"},
                                   {3, "Przystanki"},
                                   {4, "Tabor"},
                                   {0, "Wyjdz"}});

    switch (choice)
    {
    case 1:
        launchEditMenu();
        break;
    case 2:
        launchLinesMenu();
        break;
    case 3:
        cout << "Wybrano Przystanki" << endl;
        break;
    case 4:
        cout << "Wybrano Tabor" << endl;
        break;
    case 0:
        exit(0);
        break;
    default:
        cout << "Nieprawidlowa opcja, sprobuj ponownie." << endl;
        launch();
        break;
    }
}

void App::launchEditMenu()
{
    cout << "Menu edycji:" << endl;
    int choice = Utils::promptSel({{1, "Pojazdy"},
                                   {2, "Przystanki"},
                                   {3, "Trasy"},
                                   {4, "Linie"},
                                   {0, "Powrót"}});

    switch (choice)
    {
    case 1:
        launchEditVehicleMenu();
        break;
    case 0:
        launch();
        break;
    default:
        cout << "Nieprawidlowa opcja, sprobuj ponownie." << endl;
        launchEditMenu();
        break;
    }
}

void App::launchEditVehicleMenu()
{
    cout << "Edycja pojazdów:" << endl;
    int choice = Utils::promptSel({{1, "Lista pojazdów"},
                                   {2, "Dodaj pojazd"},
                                   {3, "Edytuj pojazd"},
                                   {0, "Powrót"}});

    switch (choice)
    {
    case 1:
        printVehicles();
        launchEditVehicleMenu();
        break;
    case 2:
        launchAddNewVehicle();
        break;
    case 3:
        launchEditVehicle();
        break;
    case 0:
        launchEditMenu();
        break;
    default:
        cout << "Nieprawidlowa opcja, sprobuj ponownie." << endl;
        launchEditVehicleMenu();
        break;
    }
}

void App::printVehicles()
{

    if (!vehicles.size())
    {
        cout << "Brak pojazdow." << endl;
        return;
    }

    for (uint32_t i = 0; i < vehicles.size(); i++)
    {
        Vehicle &vehicle = vehicles[i];
        cout << "[" << i << "] " << vehicle.getModel() << endl;
        cout << "  " << "Typ: " << vehicle.getTypeString() << endl;
        cout << "  " << "Rok produkcji: " << vehicle.getProdYear() << endl;
    }
}

void App::launchAddNewVehicle()
{
    string model;
    string typeStr;
    string prodYearStr;

    cout << "Dodawanie nowego pojazdu" << endl;
    cout << "Podaj model: ";
    cin.ignore(); // Ignore the newline character left in the buffer
    getline(cin, model);

    cout << "Wybierz typ: " << endl;
    int choice = Utils::promptSel({{1, "Autobus"},
                                   {2, "Tramwaj"},
                                   {3, "Trolejbus"}});
    VehicleType vehicleType;

    switch (choice)
    {
    case 1:
        vehicleType = BUS;
        break;
    case 2:
        vehicleType = TRAM;
        break;
    case 3:
        vehicleType = TROLLEYBUS;
        break;
    default:
        cout << "Nieprawidlowy typ pojazdu" << endl;
        launchEditVehicleMenu();
        break;
    }

    cout << "Podaj rok produkcji: ";
    cin >> prodYearStr;

    int prodYear = getChoiceInt(prodYearStr);

    if (prodYear < 1900 || prodYear > 2025)
    {
        cout << "Nieprawidlowy rok produkcji" << endl;
        launchEditVehicleMenu();
    }

    Vehicle newVehicle(vehicles.size(), vehicleType, model, prodYear);
    vehicles.push_back(newVehicle);
    cout << "Pojazd dodany." << endl;
    launchEditVehicleMenu();
}

void App::launchEditVehicle()
{

    cout << "Podaj ID pojazdu: ";

    string vehicleIdStr;
    int vehicleId;

    cin >> vehicleIdStr;
    vehicleId = getChoiceInt(vehicleIdStr);
    if (vehicleId < 0 || (uint32_t)vehicleId >= vehicles.size())
    {
        cout << "Nieprawidlowy ID pojazdu" << endl;
        launchEditVehicleMenu();
        return;
    }

    Vehicle &vehicle = vehicles[vehicleId];
    string model;
    string typeStr;
    string prodYearStr;

    cout << "Edycja pojazdu: " << "[" << vehicleId << "] " << vehicle.getModel() << endl;
    cout << "Aktualny model: " << vehicle.getModel() << endl;
    cout << "Podaj nowy model: ";
    cin.ignore();
    getline(cin, model);
    vehicle.setModel(model);

    cout << "Aktualny typ: " << vehicle.getTypeString() << endl;
    cout << "Wybierz nowy typ" << endl;
    int choice = Utils::promptSel({{1, "Autobus"},
                                   {2, "Tramwaj"},
                                   {3, "Trolejbus"}});
    VehicleType vehicleType;
    switch (choice)
    {
    case 1:
        vehicleType = BUS;
        break;
    case 2:
        vehicleType = TRAM;
        break;
    case 3:
        vehicleType = TROLLEYBUS;
        break;
    default:
        cout << "Nieprawidlowy typ pojazdu" << endl;
        launchEditVehicleMenu();
        return;
    }
    vehicle.setType(vehicleType);

    cout << "Aktualny rok produkcji: " << vehicle.getProdYear() << endl;
    cout << "Podaj nowy rok produkcji: ";
    cin >> prodYearStr;

    int prodYear = getChoiceInt(prodYearStr);

    if (prodYear < 1900 || prodYear > 2025)
    {
        cout << "Nieprawidlowy rok produkcji" << endl;
        launchEditVehicleMenu();
        return;
    }
    vehicle.setProdYear(prodYear);

    cout << "Pojazd zaktualizowany." << endl;
    launchEditVehicleMenu();
}

void App::launchLinesMenu()
{
    cout << "Menu linii:" << endl;
    int choice = Utils::promptSel({{1, "Wyświetl listę linii"},
                                   {2, "Wyświetl szczegóły linii"},
                                   {0, "Powrót"}});

    switch (choice)
    {
    case 1:
        printLines();
        launchLinesMenu();
        break;
    case 2:
        launchLinesDetailsMenu();
        break;
    case 0:
        launch();
        break;
    default:
        cout << "Nieprawidlowa opcja, sprobuj ponownie." << endl;
        launchEditMenu();
        break;
    }
}

vector<Stop> getUniqueStops(Line &line)
{
    std::set<Stop> uniqueStops;
    for (auto &route : line.getRoutes())
        for (auto &stop : route.getStops())
            uniqueStops.insert(stop);

    return vector<Stop>(uniqueStops.begin(), uniqueStops.end());
}

void App::printLines()
{
    cout << "Linie:" << endl;
    for (uint32_t i = 0; i < lines.size(); i++)
    {
        Line &line = lines[i];
        cout << "[" << i << "] " << line.getLineNumber() << ":" << endl;

        cout << "Przystanki:" << endl;
        vector<Stop> uniqueStops = getUniqueStops(line);
        for (uint32_t i = 0; i < uniqueStops.size(); i++)
            cout << " [" << i << "]" << uniqueStops[i].getName() << endl;
    }
}

void App::launchLinesDetailsMenu()
{
    cout << "Podaj ID linii: " << endl;

    int choice;
    cin >> choice;

    // TODO validate
    Line &line = lines[choice];

    launchLineDetailsMenu(line);
}

void App::launchLineDetailsMenu(Line &line)
{
    int choice = Utils::promptSel({{1, "Wyświetl przystanki"},
                                   {0, "Powrót"}});

    switch (choice)
    {
    case 1:
        launchLineStopsMenu(line);
        break;
    case 0:
        launchLinesMenu();
        break;
    default:
        launchLineDetailsMenu(line);
        break;
    }
}

void App::launchLineStopsMenu(Line &line)
{
    vector<Stop> uniqueStops = getUniqueStops(line);

    cout << "Przystanki:" << endl;
    for (uint32_t i = 0; i < uniqueStops.size(); i++)
    {
        Stop &stop = uniqueStops[i];
        cout << "[" << i << "] " << stop.getName() << endl;
    }

    cout << "Podaj ID przystanku: " << endl;

    int choice;
    cin >> choice;

    // TODO validate
    Stop &stop = uniqueStops[choice];

    cout << "Rozkład dla przystanku: " << stop.getName() << endl;
    Schedule::printScheduleForStop(stop, line);

    launchLineDetailsMenu(line);
}
#include "stop.h"
#include <stdexcept>
#include <string>
#include <vector>

using std::runtime_error;
using std::string;
using std::vector;

Stop::Stop(string name, int id, TransportType stopType)
    : name(name), id(id), stopType(stopType) {}

string Stop::getName() const { return name; }
void Stop::setName(string name) { this->name = name; }

int Stop::getId() const { return id; }
void Stop::setId(int id) { this->id = id; }

TransportType Stop::getType() const { return stopType; }
string Stop::getTypeString() const {
  switch (stopType) {
  case TransportType::BUS:
    return "autobus";
  case TransportType::TRAM:
    return "tramwaj";
  default:
    throw runtime_error("Unknown TransportType");
  }
}
void Stop::setType(TransportType type) { stopType = type; }

bool Stop::operator<(const Stop &other) const { return id < other.id; }

bool Stop::operator==(const Stop &other) const { return id == other.id; }

Stop &Stop::getStopById(vector<Stop> &stops, int stopId) {
  for (auto &stop : stops) {
    if (stop.getId() == stopId) {
      return stop;
    }
  }
  throw runtime_error("Stop not found");
}
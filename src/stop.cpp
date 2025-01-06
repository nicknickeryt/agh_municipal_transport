#include <string>
#include "stop.h"

using namespace std;

 Stop::Stop(string name) : name(name) {}
  Stop::Stop(string name, int id) : name(name), id(id) {}

  string Stop::getName() const { return name; }
  void Stop::setName(string name) { this->name = name; }

  int Stop::getId() const { return id; }
  void Stop::setId(int id) { this->id = id; }

  bool Stop::operator<(const Stop &other) const {
    return id < other.id || (id == other.id && name < other.name);
  }

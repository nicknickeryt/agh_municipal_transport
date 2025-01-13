#ifndef STOP_H
#define STOP_H

#include <string>
#include <vector>

#include <boost/serialization/map.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

#include "enums.h"

using std::string;
using std::vector;

class Stop {
private:
  string name;
  int id;
  TransportType stopType;

public:
  Stop() = default;
  Stop(string name, int id, TransportType stopType);

  string getName() const;
  void setName(string name);

  int getId() const;
  void setId(int id);

  TransportType getType() const;
  string getTypeString() const;
  void setType(TransportType type);

  bool operator<(const Stop &other) const;

  bool operator==(const Stop &other) const;

  static Stop &getStopById(vector<Stop> &stops, int stopId);

  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    (void)version;
    ar & name;
    ar & id;
    ar & stopType;
  }
};

#endif // STOP_H
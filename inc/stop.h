#ifndef STOP_H
#define STOP_H

#include <string>
#include <vector>

#include <boost/serialization/map.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

using std::string;
using std::vector;

class Stop {
private:
  string name;
  int id;

public:
  Stop() = default;
  Stop(string name);
  Stop(string name, int id);

  string getName() const;
  void setName(string name);

  int getId() const;
  void setId(int id);

  bool operator<(const Stop &other) const;

  bool operator==(const Stop &other) const;

  static Stop& getStopById(vector<Stop> &stops, int stopId); 

  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    (void)version;
    ar & name;   
    ar & id;
  }
};

#endif // STOP_H
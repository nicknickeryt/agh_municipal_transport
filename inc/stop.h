#pragma once

#include <string>
#include <vector>

using namespace std;

class Stop {
private:
  string name;
  int id;

public:
  Stop(string name);
  Stop(string name, int id);

  string getName() const;
  void setName(string name);

  int getId() const;
  void setId(int id);

  bool operator<(const Stop &other) const;

  bool operator==(const Stop &other) const;

  static Stop getStopById(vector<Stop> &stops, int stopId); 
};
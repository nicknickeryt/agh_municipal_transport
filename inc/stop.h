#pragma once

#include <string>

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
};
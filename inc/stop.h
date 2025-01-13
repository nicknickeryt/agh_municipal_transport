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

/**
 * @brief Represents a transport stop.
 */
class Stop {
private:
  string name;
  int id;
  TransportType stopType;

public:
  /**
   * @brief Default constructor.
   */
  Stop() = default;

  /**
   * @brief Parameterized constructor.
   * @param name Name of the stop.
   * @param id Unique identifier for the stop.
   * @param stopType Type of transport for the stop.
   */
  Stop(string name, int id, TransportType stopType);

  /**
   * @brief Get the name of the stop.
   * @return The name of the stop.
   */
  string getName() const;

  /**
   * @brief Set the name of the stop.
   * @param name The new name of the stop.
   */
  void setName(string name);

  /**
   * @brief Get the unique identifier of the stop.
   * @return The unique identifier of the stop.
   */
  int getId() const;

  /**
   * @brief Set the unique identifier of the stop.
   * @param id The new unique identifier of the stop.
   */
  void setId(int id);

  /**
   * @brief Get the type of transport for the stop.
   * @return The type of transport for the stop.
   */
  TransportType getType() const;

  /**
   * @brief Get the type of transport as a string.
   * @return The type of transport as a string.
   */
  string getTypeString() const;

  /**
   * @brief Set the type of transport for the stop.
   * @param type The new type of transport for the stop.
   */
  void setType(TransportType type);

  /**
   * @brief Comparison operator for sorting stops.
   * @param other The other stop to compare with.
   * @return True if this stop is less than the other stop, false otherwise.
   */
  bool operator<(const Stop &other) const;

  /**
   * @brief Equality operator to compare two stops.
   * @param other The other stop to compare with.
   * @return True if the stops are equal, false otherwise.
   */
  bool operator==(const Stop &other) const;

  /**
   * @brief Get a stop by its ID from a vector of stops.
   * @param stops The vector of stops.
   * @param stopId The ID of the stop to find.
   * @return A reference to the stop with the given ID.
   */
  static Stop &getStopById(vector<Stop> &stops, int stopId);

  /**
   * @brief Serialization function for Boost.Serialization.
   * @param ar The archive to serialize to.
   * @param version The version of the serialization.
   */
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
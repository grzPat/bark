// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.


#ifndef MODULES_WORLD_OPENDRIVE_JUNCTION_HPP_
#define MODULES_WORLD_OPENDRIVE_JUNCTION_HPP_

#include <map>
#include <vector>
#include <string>

namespace modules {
namespace world {
namespace opendrive {

class Junction {
 public:
  Junction(const std::string& name, uint32_t id) : id_(id), name_(name) {}
  Junction() {}
  ~Junction() {}

  using Connections = std::map<uint32_t, Connection>;

  //! setter functions
  void add_connection(Connection con) { connections_[con.id_] = con; }
  void set_id(uint32_t id) { id_ = id; }

  //! getter functions
  Connections get_connections() const { return connections_; }
  Connection get_connection(uint32_t id) const { return connections_.at(id); }
  uint32_t get_id() const { return id_; }

 private:
  uint32_t id_;
  std::string name_;
  Connections connections_;
};

using JunctionPtr = std::shared_ptr<Junction>;

}  // namespace opendrive
}  // namespace world
}  // namespace modules

#endif  // MODULES_WORLD_OPENDRIVE_JUNCTION_HPP_

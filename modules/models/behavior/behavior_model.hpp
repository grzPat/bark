// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.


#ifndef MODULES_MODELS_BEHAVIOR_BEHAVIOR_MODEL_HPP_
#define MODULES_MODELS_BEHAVIOR_BEHAVIOR_MODEL_HPP_

#include <memory>

#include "modules/commons/base_type.hpp"
#include "modules/models/dynamic/dynamic_model.hpp"

namespace modules {
namespace world {
namespace objects {
class Agent;
typedef std::shared_ptr<Agent> AgentPtr;
typedef unsigned int AgentId;
}  // namespace objects
class ObservedWorld;
}  // namespace world
namespace models {
namespace behavior {
using dynamic::Trajectory;

class BehaviorModel : public modules::commons::BaseType {
 public:
  explicit BehaviorModel(commons::Params *params) : commons::BaseType(params),
                                                    last_trajectory_() {}

  BehaviorModel(const BehaviorModel &behavior_model) : 
              commons::BaseType(behavior_model.get_params()),
              last_trajectory_(behavior_model.get_last_trajectory()) {}

  virtual ~BehaviorModel() {}

  dynamic::Trajectory get_last_trajectory() const { return last_trajectory_; }

  void set_last_trajectory(const dynamic::Trajectory &trajectory) {
    last_trajectory_ = trajectory;
  }

  virtual Trajectory Plan(float delta_time,
                          const world::ObservedWorld& observed_world) = 0;

  virtual BehaviorModel *Clone() const = 0;

 private:
  dynamic::Trajectory last_trajectory_;
};

typedef std::shared_ptr<BehaviorModel> BehaviorModelPtr;

}  // namespace behavior
}  // namespace models
}  // namespace modules

#endif  // MODULES_MODELS_BEHAVIOR_BEHAVIOR_MODEL_HPP_

// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.


#include "modules/world/world.hpp"
#include "modules/world/observed_world.hpp"
#include "modules/world/map/roadgraph.hpp"
#include "python/world/world.hpp"
#include "python/world/agent.hpp"
#include "python/world/map.hpp"
#include "python/world/opendrive.hpp"

namespace py = pybind11;
using namespace modules::world::objects;
using namespace modules::world::map;
using namespace modules::models::dynamic;
using namespace modules::commons;
using namespace modules::models::behavior;
using namespace modules::geometry;
using namespace modules::world;

void python_world(py::module m) {
  py::class_<World, std::shared_ptr<World>>(m, "World")
    .def(py::init<Params *>())
    .def("__repr__", [](const World &a) {
      return "bark.world.World";
    })
    .def("step", &World::Step)
    .def("add_agent", &World::add_agent)
    .def("add_object", &World::add_object)
    .def("set_map", &World::set_map)
    .def_property_readonly("agents", &World::get_agents)
    .def_property_readonly("objects", &World::get_objects)
    .def_property_readonly("time", &World::get_world_time)
    .def_property_readonly("agent", &World::get_agent)
    .def_property("map", &World::get_map, &World::set_map);


  py::class_<ObservedWorld, std::shared_ptr<ObservedWorld>>(m, "ObservedWorld")
      .def(py::init<const World&, const AgentId&>())
      .def("__repr__", [](const ObservedWorld &a) {
        return "bark.world.ObservedWorld";
      });

  python_agent(m.def_submodule("agent", "Agent wrapping"));
  python_opendrive(m.def_submodule("opendrive", "OpenDrive wrapping"));
  python_map(m.def_submodule("map", "mapInterface wrapping"));

  py::class_<vertex_t>(m, "vertex_t")
    .def(py::init<>());

  py::class_<edge_t>(m, "edge_t")
    .def(py::init<>());

  py::class_<LaneVertex, std::shared_ptr<LaneVertex>>(m, "LaneVertex")
    .def(py::init<int, int, LanePtr>())
    .def_property_readonly("lane_id", &LaneVertex::get_global_line_id)
    .def_property_readonly("lane", &LaneVertex::get_lane);

  py::enum_<LaneEdgeType>(m, "LaneEdgeType")
    .value("SUCCESSOR_EDGE", LaneEdgeType::SUCCESSOR_EDGE)
    .value("INNER_NEIGHBOR_EDGE", LaneEdgeType::INNER_NEIGHBOR_EDGE)
    .value("OUTER_NEIGHBOR_EDGE", LaneEdgeType::OUTER_NEIGHBOR_EDGE)
    .export_values();

  py::class_<LaneEdge, std::shared_ptr<LaneEdge>>(m, "LaneEdge")
    .def(py::init<LaneEdgeType>())
    .def_property_readonly("edge_type", &LaneEdge::get_edge_type);

}

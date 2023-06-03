#pragma once

#include <third_party/json.h>

#include "src/models/waypoint_type.h"

struct SystemWaypoint {
 public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(SystemWaypoint, symbol, type, x, y)

 public:
  std::string symbol;
  WaypointType type{};
  int64_t x = 0;
  int64_t y = 0;
};
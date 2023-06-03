#pragma once

#include <third_party/json.h>

#include "src/models/system_faction.h"
#include "src/models/system_type.h"
#include "src/models/system_waypoint.h"

struct System {
 public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(System, symbol, sectorSymbol, type, x, y,
                                 waypoints, factions)

 public:
  std::string symbol;
  std::string sectorSymbol;
  SystemType type{};
  int64_t x = 0;
  int64_t y = 0;
  std::vector<SystemWaypoint> waypoints;
  std::vector<SystemFaction> factions;
};
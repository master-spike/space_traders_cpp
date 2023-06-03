#pragma once

#include <third_party/json.h>

#include "src/models/ship_cargo_item.h"

struct ShipCargo {
 public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(ShipCargo, capacity, units, inventory)

 public:
  uint64_t capacity = 0;
  uint64_t units = 0;
  std::vector<ShipCargoItem> inventory;
};
#pragma once

#include <third_party/json.h>

#include "src/models/system.h"

struct GetSystemRequest {
 public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(GetSystemRequest, systemSymbol)

 public:
  std::string systemSymbol;
};
struct GetSystemResponse {
 public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(GetSystemResponse, data)

 public:
  System data;
};
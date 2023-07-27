#pragma once

#include "cpp-httplib/httplib.h"
#include "nlohmann/json.hpp"
#include "space_traders_cpp/api/agents/my_agent.h"
#include "space_traders_cpp/api/contracts/accept_contract.h"
#include "space_traders_cpp/api/contracts/deliver_contract.h"
#include "space_traders_cpp/api/contracts/fulfill_contract.h"
#include "space_traders_cpp/api/contracts/get_contract.h"
#include "space_traders_cpp/api/contracts/list_contracts.h"
#include "space_traders_cpp/api/factions/get_faction.h"
#include "space_traders_cpp/api/factions/list_factions.h"
#include "space_traders_cpp/api/fleet/create_chart.h"
#include "space_traders_cpp/api/fleet/create_survey.h"
#include "space_traders_cpp/api/fleet/dock_ship.h"
#include "space_traders_cpp/api/fleet/extract_resources.h"
#include "space_traders_cpp/api/fleet/get_mounts.h"
#include "space_traders_cpp/api/fleet/get_ship.h"
#include "space_traders_cpp/api/fleet/get_ship_cargo.h"
#include "space_traders_cpp/api/fleet/get_ship_cooldown.h"
#include "space_traders_cpp/api/fleet/get_ship_nav.h"
#include "space_traders_cpp/api/fleet/install_mount.h"
#include "space_traders_cpp/api/fleet/jettison_cargo.h"
#include "space_traders_cpp/api/fleet/jump_ship.h"
#include "space_traders_cpp/api/fleet/list_ships.h"
#include "space_traders_cpp/api/fleet/navigate_ship.h"
#include "space_traders_cpp/api/fleet/negotiate_contract.h"
#include "space_traders_cpp/api/fleet/orbit_ship.h"
#include "space_traders_cpp/api/fleet/patch_ship_nav.h"
#include "space_traders_cpp/api/fleet/purchase_cargo.h"
#include "space_traders_cpp/api/fleet/purchase_ship.h"
#include "space_traders_cpp/api/fleet/refuel_ship.h"
#include "space_traders_cpp/api/fleet/remove_mount.h"
#include "space_traders_cpp/api/fleet/scan_ships.h"
#include "space_traders_cpp/api/fleet/scan_systems.h"
#include "space_traders_cpp/api/fleet/scan_waypoints.h"
#include "space_traders_cpp/api/fleet/sell_cargo.h"
#include "space_traders_cpp/api/fleet/ship_refine.h"
#include "space_traders_cpp/api/fleet/transfer_cargo.h"
#include "space_traders_cpp/api/fleet/warp_ship.h"
#include "space_traders_cpp/api/register.h"
#include "space_traders_cpp/api/status.h"
#include "space_traders_cpp/api/systems/get_jump_gate.h"
#include "space_traders_cpp/api/systems/get_market.h"
#include "space_traders_cpp/api/systems/get_shipyard.h"
#include "space_traders_cpp/api/systems/get_system.h"
#include "space_traders_cpp/api/systems/get_waypoint.h"
#include "space_traders_cpp/api/systems/list_systems.h"
#include "space_traders_cpp/api/systems/list_waypoints.h"
#include "space_traders_cpp/i_client.h"
#include "space_traders_cpp/utility.h"
#include "space_traders_cpp/ratelimiter.h"

struct LoginRequest {
 public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(LoginRequest, token)

 public:
  std::string token;
};

struct RequestError {
 public:
  explicit RequestError(int32_t http_status, std::string body)
      : http_status(http_status), body(body) {}

 public:
  int32_t http_status = -1;
  std::string body;
};

class Session {
 public:
  explicit Session();
  explicit Session(const std::string token);
  explicit Session(const std::shared_ptr<IClient> client);
  explicit Session(const std::shared_ptr<IClient> client,
                   const std::string token);
  explicit Session(const int rate_limit); // in milliseconds
  explicit Session(const std::string token, const int rate_limit);
  explicit Session(const std::shared_ptr<IClient> client, const int rate_limit);
  explicit Session(const std::shared_ptr<IClient> client,
                   const std::string token, const int rate_limit);


  bool IsAPIOnline();
  bool IsLoggedIn();

  Result<MyAgentResponse, RequestError> Login(const LoginRequest& req);

  Result<StatusResponse, RequestError> Status(const StatusRequest& req);
  Result<RegisterResponse, RequestError> Register(
      const RegisterRequest& req);

  Result<MyAgentResponse, RequestError> MyAgent(
      const MyAgentRequest& req);

  Result<ListContractsResponse, RequestError> ListContracts(
      const ListContractsRequest& req);
  Result<GetContractResponse, RequestError> GetContract(
      const GetContractRequest& req);
  Result<AcceptContractResponse, RequestError> AcceptContract(
      const AcceptContractRequest& req);
  Result<DeliverContractResponse, RequestError> DeliverContract(
      const DeliverContractRequest& req);
  Result<FulfillContractResponse, RequestError> FulfillContract(
      const FulfillContractRequest& req);

  Result<ListFactionsResponse, RequestError> ListFactions(
      const ListFactionsRequest& req);
  Result<GetFactionResponse, RequestError> GetFaction(
      const GetFactionRequest& req);

  Result<ListShipsResponse, RequestError> ListShips(
      const ListShipsRequest& req);
  Result<PurchaseShipResponse, RequestError> PurchaseShip(
      const PurchaseShipRequest& req);
  Result<GetShipResponse, RequestError> GetShip(
      const GetShipRequest& req);
  Result<GetShipCargoResponse, RequestError> GetShipCargo(
      const GetShipCargoRequest& req);
  Result<OrbitShipResponse, RequestError> OrbitShip(
      const OrbitShipRequest& req);
  Result<ShipRefineResponse, RequestError> ShipRefine(
      const ShipRefineRequest& req);
  Result<CreateChartResponse, RequestError> CreateChart(
      const CreateChartRequest& req);
  Result<GetShipCooldownResponse, RequestError> GetShipCooldown(
      const GetShipCooldownRequest& req);
  Result<DockShipResponse, RequestError> DockShip(
      const DockShipRequest& req);
  Result<CreateSurveyResponse, RequestError> CreateSurvey(
      const CreateSurveyRequest& req);
  Result<ExtractResourcesResponse, RequestError> ExtractResources(
      const ExtractResourcesRequest& req);
  Result<JettisonCargoResponse, RequestError> JettisonCargo(
      const JettisonCargoRequest& req);
  Result<JumpShipResponse, RequestError> JumpShip(
      const JumpShipRequest& req);
  Result<NavigateShipResponse, RequestError> NavigateShip(
      const NavigateShipRequest& req);
  Result<PatchShipNavResponse, RequestError> PatchShipNav(
      const PatchShipNavRequest& req);
  Result<GetShipNavResponse, RequestError> GetShipNav(
      const GetShipNavRequest& req);
  Result<WarpShipResponse, RequestError> WarpShip(
      const WarpShipRequest& req);
  Result<SellCargoResponse, RequestError> SellCargo(
      const SellCargoRequest& req);
  Result<ScanSystemsResponse, RequestError> ScanSystems(
      const ScanSystemsRequest& req);
  Result<ScanWaypointsResponse, RequestError> ScanWaypoints(
      const ScanWaypointsRequest& req);
  Result<ScanShipsResponse, RequestError> ScanShips(
      const ScanShipsRequest& req);
  Result<RefuelShipResponse, RequestError> RefuelShip(
      const RefuelShipRequest& req);
  Result<PurchaseCargoResponse, RequestError> PurchaseCargo(
      const PurchaseCargoRequest& req);
  Result<TransferCargoResponse, RequestError> TransferCargo(
      const TransferCargoRequest& req);
  Result<NegotiateContractResponse, RequestError> NegotiateContract(
      const NegotiateContractRequest& req);
  Result<GetMountsResponse, RequestError> GetMounts(
      const GetMountsRequest& req);
  Result<InstallMountResponse, RequestError> InstallMount(
      const InstallMountRequest& req);
  Result<RemoveMountResponse, RequestError> RemoveMount(
      const RemoveMountRequest& req);

  Result<ListSystemsResponse, RequestError> ListSystems(
      const ListSystemsRequest& req);
  Result<GetSystemResponse, RequestError> GetSystem(
      const GetSystemRequest& req);
  Result<ListWaypointsResponse, RequestError> ListWaypoints(
      const ListWaypointsRequest& req);
  Result<GetWaypointResponse, RequestError> GetWaypoint(
      const GetWaypointRequest& req);
  Result<GetMarketResponse, RequestError> GetMarket(
      const GetMarketRequest& req);
  Result<GetShipyardResponse, RequestError> GetShipyard(
      const GetShipyardRequest& req);
  Result<GetJumpGateResponse, RequestError> GetJumpGate(
      const GetJumpGateRequest& req);

 private:
  template <typename R>
  httplib::Result MakeGet(const R& request) const {
    return client_->Get(kBasePath + request.FormattedPath(),
                        request.HttplibParams(), httplib::Headers{});
  }
  template <typename R>
  httplib::Result MakePost(
      const R& request, std::string content_type = "application/json") const {
    const nlohmann::json j = request.body;
    return client_->Post(kBasePath + request.FormattedPath(), j.dump(),
                         content_type);
  }
  template <typename R>
  httplib::Result MakePatch(
      const R& request, std::string content_type = "application/json") const {
    const nlohmann::json j = request.body;
    return client_->Patch(kBasePath + request.FormattedPath(), j.dump(),
                          content_type);
  }
  template <typename R>
  httplib::Result MakeAuthGet(const R& request) const {
    return client_->Get(
        kBasePath + request.FormattedPath(), request.HttplibParams(),
        httplib::Headers{{"Authorization", "Bearer " + token_}});
  }
  template <typename R>
  httplib::Result MakeAuthPost(
      const R& request, std::string content_type = "application/json") const {
    constexpr bool has_to_json =
        requires(const R& r, nlohmann::json j) { j = r.body; };

    if constexpr (has_to_json) {
      const nlohmann::json j = request.body;
      return client_->Post(
          kBasePath + request.FormattedPath(),
          httplib::Headers{{"Authorization", "Bearer " + token_}}, j.dump(),
          content_type);
    } else {
      return client_->Post(
          kBasePath + request.FormattedPath(),
          httplib::Headers{{"Authorization", "Bearer " + token_}});
    }
  }
  template <typename R>
  httplib::Result MakeAuthPatch(
      const R& request, std::string content_type = "application/json") const {
    const nlohmann::json j = request.body;
    return client_->Patch(
        kBasePath + request.FormattedPath(),
        httplib::Headers{{"Authorization", "Bearer " + token_}}, j.dump(),
        content_type);
  }

  template <typename R>
  Result<R, RequestError> ResponseBodyOrError(
      const httplib::Result& result) const {
    if (result->status != R::kValidStatus) {
      const RequestError err(result->status, result->body);
      return Err(err);
    }

    const nlohmann::json j = nlohmann::json::parse(result->body);
    R response = j.get<R>();
    response.http_status = result->status;
    return Ok(response);
  }

 private:
  std::string token_;
  std::shared_ptr<IClient> client_;
  static const std::string kBasePath;
  RateLimiter rate_limiter_;
};
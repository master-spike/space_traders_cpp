#include "space_traders_cpp/session.h"

#include "space_traders_cpp/client.h"
#include "space_traders_cpp/utility.h"

const std::string Session::kBasePath = "/v2";

Session::Session()
    : client_(std::make_shared<Client>("https://api.spacetraders.io")), rate_limiter_() {}
Session::Session(std::string token)
    : token_(token),
      client_(std::make_shared<Client>("https://api.spacetraders.io")),
      rate_limiter_() {}
Session::Session(std::shared_ptr<IClient> client) : client_(client), rate_limiter_() {}
Session::Session(std::shared_ptr<IClient> client, std::string token)
    : token_(token), client_(client), rate_limiter_() {}
Session::Session(int rate_limit) : client_(std::make_shared<Client>("https://api.spacetraders.io")), rate_limiter_(rate_limit) {}
Session::Session(std::string token, int rate_limit)
    : token_(token),
      client_(std::make_shared<Client>("https://api.spacetraders.io")),
      rate_limiter_(rate_limit) {}
Session::Session(std::shared_ptr<IClient> client, int rate_limit) : client_(client), rate_limiter_(rate_limit) {}
Session::Session(std::shared_ptr<IClient> client, std::string token, int rate_limit)
    : token_(token), client_(client), rate_limiter_(rate_limit) {}

bool Session::IsAPIOnline() {
  rate_limiter_.rl_wait();
  const Result<StatusResponse, RequestError> status_res =
      Status(StatusRequest{});
  if (status_res.IsErr()) {
    return false;
  }
  return status_res.Ok().status.find("online") != std::string::npos;
}
bool Session::IsLoggedIn() { rate_limiter_.rl_wait(); return MyAgent(MyAgentRequest{}).IsOk(); }

Result<MyAgentResponse, RequestError> Session::Login(const LoginRequest& req) {
  rate_limiter_.rl_wait();
  token_ = req.token;
  return MyAgent(MyAgentRequest{});
}
Result<StatusResponse, RequestError> Session::Status(
    const StatusRequest& req) {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeGet(req);
  return ResponseBodyOrError<StatusResponse>(result);
}
Result<RegisterResponse, RequestError> Session::Register(
    const RegisterRequest& req) {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakePost(req);
  return ResponseBodyOrError<RegisterResponse>(result);
}

Result<MyAgentResponse, RequestError> Session::MyAgent(
    const MyAgentRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthGet(req);
  return ResponseBodyOrError<MyAgentResponse>(result);
}

Result<ListContractsResponse, RequestError> Session::ListContracts(
    const ListContractsRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthGet(req);
  return ResponseBodyOrError<ListContractsResponse>(result);
}
Result<GetContractResponse, RequestError> Session::GetContract(
    const GetContractRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthGet(req);
  return ResponseBodyOrError<GetContractResponse>(result);
}
Result<AcceptContractResponse, RequestError> Session::AcceptContract(
    const AcceptContractRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<AcceptContractResponse>(result);
}
Result<DeliverContractResponse, RequestError> Session::DeliverContract(
    const DeliverContractRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<DeliverContractResponse>(result);
}
Result<FulfillContractResponse, RequestError> Session::FulfillContract(
    const FulfillContractRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<FulfillContractResponse>(result);
}

Result<ListFactionsResponse, RequestError> Session::ListFactions(
    const ListFactionsRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeGet(req);
  return ResponseBodyOrError<ListFactionsResponse>(result);
}
Result<GetFactionResponse, RequestError> Session::GetFaction(
    const GetFactionRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeGet(req);
  return ResponseBodyOrError<GetFactionResponse>(result);
}

Result<ListShipsResponse, RequestError> Session::ListShips(
    const ListShipsRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthGet(req);
  return ResponseBodyOrError<ListShipsResponse>(result);
}
Result<PurchaseShipResponse, RequestError> Session::PurchaseShip(
    const PurchaseShipRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<PurchaseShipResponse>(result);
}
Result<GetShipResponse, RequestError> Session::GetShip(
    const GetShipRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthGet(req);
  return ResponseBodyOrError<GetShipResponse>(result);
}
Result<GetShipCargoResponse, RequestError> Session::GetShipCargo(
    const GetShipCargoRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthGet(req);
  return ResponseBodyOrError<GetShipCargoResponse>(result);
}
Result<OrbitShipResponse, RequestError> Session::OrbitShip(
    const OrbitShipRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<OrbitShipResponse>(result);
}
Result<ShipRefineResponse, RequestError> Session::ShipRefine(
    const ShipRefineRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<ShipRefineResponse>(result);
}
Result<CreateChartResponse, RequestError> Session::CreateChart(
    const CreateChartRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<CreateChartResponse>(result);
}
Result<GetShipCooldownResponse, RequestError> Session::GetShipCooldown(
    const GetShipCooldownRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthGet(req);
  // Special case with two valid response status
  if (result->status != GetShipCooldownResponse::kValidStatus &&
      result->status != GetShipCooldownResponse::kNoCooldownStatus) {
    const RequestError err(result->status, result->body);
    return Err(err);
  }

  const nlohmann::json j = nlohmann::json::parse(result->body);
  GetShipCooldownResponse response = j.get<GetShipCooldownResponse>();
  response.http_status = result->status;
  return Ok(response);
}
Result<DockShipResponse, RequestError> Session::DockShip(
    const DockShipRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<DockShipResponse>(result);
}
Result<CreateSurveyResponse, RequestError> Session::CreateSurvey(
    const CreateSurveyRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<CreateSurveyResponse>(result);
}
Result<ExtractResourcesResponse, RequestError> Session::ExtractResources(
    const ExtractResourcesRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<ExtractResourcesResponse>(result);
}
Result<JettisonCargoResponse, RequestError> Session::JettisonCargo(
    const JettisonCargoRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<JettisonCargoResponse>(result);
}
Result<JumpShipResponse, RequestError> Session::JumpShip(
    const JumpShipRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<JumpShipResponse>(result);
}
Result<NavigateShipResponse, RequestError> Session::NavigateShip(
    const NavigateShipRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<NavigateShipResponse>(result);
}
Result<PatchShipNavResponse, RequestError> Session::PatchShipNav(
    const PatchShipNavRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPatch(req);
  return ResponseBodyOrError<PatchShipNavResponse>(result);
}
Result<GetShipNavResponse, RequestError> Session::GetShipNav(
    const GetShipNavRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthGet(req);
  return ResponseBodyOrError<GetShipNavResponse>(result);
}
Result<WarpShipResponse, RequestError> Session::WarpShip(
    const WarpShipRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<WarpShipResponse>(result);
}
Result<SellCargoResponse, RequestError> Session::SellCargo(
    const SellCargoRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<SellCargoResponse>(result);
}
Result<ScanSystemsResponse, RequestError> Session::ScanSystems(
    const ScanSystemsRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<ScanSystemsResponse>(result);
}
Result<ScanWaypointsResponse, RequestError> Session::ScanWaypoints(
    const ScanWaypointsRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<ScanWaypointsResponse>(result);
}
Result<ScanShipsResponse, RequestError> Session::ScanShips(
    const ScanShipsRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<ScanShipsResponse>(result);
}
Result<RefuelShipResponse, RequestError> Session::RefuelShip(
    const RefuelShipRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<RefuelShipResponse>(result);
}
Result<PurchaseCargoResponse, RequestError> Session::PurchaseCargo(
    const PurchaseCargoRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<PurchaseCargoResponse>(result);
}
Result<TransferCargoResponse, RequestError> Session::TransferCargo(
    const TransferCargoRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<TransferCargoResponse>(result);
}
Result<NegotiateContractResponse, RequestError> Session::NegotiateContract(
    const NegotiateContractRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<NegotiateContractResponse>(result);
}
Result<GetMountsResponse, RequestError> Session::GetMounts(
    const GetMountsRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthGet(req);
  return ResponseBodyOrError<GetMountsResponse>(result);
}
Result<InstallMountResponse, RequestError> Session::InstallMount(
    const InstallMountRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<InstallMountResponse>(result);
}
Result<RemoveMountResponse, RequestError> Session::RemoveMount(
    const RemoveMountRequest& req) const {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeAuthPost(req);
  return ResponseBodyOrError<RemoveMountResponse>(result);
}

Result<ListSystemsResponse, RequestError> Session::ListSystems(
    const ListSystemsRequest& req) {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeGet(req);
  return ResponseBodyOrError<ListSystemsResponse>(result);
}
Result<GetSystemResponse, RequestError> Session::GetSystem(
    const GetSystemRequest& req) {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeGet(req);
  return ResponseBodyOrError<GetSystemResponse>(result);
}
Result<ListWaypointsResponse, RequestError> Session::ListWaypoints(
    const ListWaypointsRequest& req) {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeGet(req);
  return ResponseBodyOrError<ListWaypointsResponse>(result);
}
Result<GetWaypointResponse, RequestError> Session::GetWaypoint(
    const GetWaypointRequest& req) {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeGet(req);
  return ResponseBodyOrError<GetWaypointResponse>(result);
}
Result<GetMarketResponse, RequestError> Session::GetMarket(
    const GetMarketRequest& req) {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeGet(req);
  return ResponseBodyOrError<GetMarketResponse>(result);
}
Result<GetShipyardResponse, RequestError> Session::GetShipyard(
    const GetShipyardRequest& req) {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeGet(req);
  return ResponseBodyOrError<GetShipyardResponse>(result);
}
Result<GetJumpGateResponse, RequestError> Session::GetJumpGate(
    const GetJumpGateRequest& req) {
  rate_limiter_.rl_wait();
  const httplib::Result result = MakeGet(req);
  return ResponseBodyOrError<GetJumpGateResponse>(result);
}
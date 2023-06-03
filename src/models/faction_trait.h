#pragma once

#include <third_party/json.h>

enum class FactionTraitSymbol {
  BUREAUCRATIC,
  SECRETIVE,
  CAPITALISTIC,
  INDUSTRIOUS,
  PEACEFUL,
  DISTRUSTFUL,
  WELCOMING,
  SMUGGLERS,
  SCAVENGERS,
  REBELLIOUS,
  EXILES,
  PIRATES,
  RAIDERS,
  CLAN,
  GUILD,
  DOMINION,
  FRINGE,
  FORSAKEN,
  ISOLATED,
  LOCALIZED,
  ESTABLISHED,
  NOTABLE,
  DOMINANT,
  INESCAPABLE,
  INNOVATIVE,
  BOLD,
  VISIONARY,
  CURIOUS,
  DARING,
  EXPLORATORY,
  RESOURCEFUL,
  FLEXIBLE,
  COOPERATIVE,
  UNITED,
  STRATEGIC,
  INTELLIGENT,
  RESEARCH_FOCUSED,
  COLLABORATIVE,
  PROGRESSIVE,
  MILITARISTIC,
  TECHNOLOGICALLY_ADVANCED,
  AGGRESSIVE,
  IMPERIALISTIC,
  TREASURE_HUNTERS,
  DEXTEROUS,
  UNPREDICTABLE,
  BRUTAL,
  FLEETING,
  ADAPTABLE,
  SELF_SUFFICIENT,
  DEFENSIVE,
  PROUD,
  DIVERSE,
  INDEPENDENT,
  SELF_INTERESTED,
  FRAGMENTED,
  COMMERCIAL,
  FREE_MARKETS,
  ENTREPRENEURIAL,
};

NLOHMANN_JSON_SERIALIZE_ENUM(
    FactionTraitSymbol,
    {
        {FactionTraitSymbol::BUREAUCRATIC, "BUREAUCRATIC"},
        {FactionTraitSymbol::SECRETIVE, "SECRETIVE"},
        {FactionTraitSymbol::CAPITALISTIC, "CAPITALISTIC"},
        {FactionTraitSymbol::INDUSTRIOUS, "INDUSTRIOUS"},
        {FactionTraitSymbol::PEACEFUL, "PEACEFUL"},
        {FactionTraitSymbol::DISTRUSTFUL, "DISTRUSTFUL"},
        {FactionTraitSymbol::WELCOMING, "WELCOMING"},
        {FactionTraitSymbol::SMUGGLERS, "SMUGGLERS"},
        {FactionTraitSymbol::SCAVENGERS, "SCAVENGERS"},
        {FactionTraitSymbol::REBELLIOUS, "REBELLIOUS"},
        {FactionTraitSymbol::EXILES, "EXILES"},
        {FactionTraitSymbol::PIRATES, "PIRATES"},
        {FactionTraitSymbol::RAIDERS, "RAIDERS"},
        {FactionTraitSymbol::CLAN, "CLAN"},
        {FactionTraitSymbol::GUILD, "GUILD"},
        {FactionTraitSymbol::DOMINION, "DOMINION"},
        {FactionTraitSymbol::FRINGE, "FRINGE"},
        {FactionTraitSymbol::FORSAKEN, "FORSAKEN"},
        {FactionTraitSymbol::LOCALIZED, "LOCALIZED"},
        {FactionTraitSymbol::ESTABLISHED, "ESTABLISHED"},
        {FactionTraitSymbol::NOTABLE, "NOTABLE"},
        {FactionTraitSymbol::DOMINANT, "DOMINANT"},
        {FactionTraitSymbol::INESCAPABLE, "INESCAPABLE"},
        {FactionTraitSymbol::INNOVATIVE, "INNOVATIVE"},
        {FactionTraitSymbol::BOLD, "BOLD"},
        {FactionTraitSymbol::VISIONARY, "VISIONARY"},
        {FactionTraitSymbol::CURIOUS, "CURIOUS"},
        {FactionTraitSymbol::DARING, "DARING"},
        {FactionTraitSymbol::EXPLORATORY, "EXPLORATORY"},
        {FactionTraitSymbol::RESOURCEFUL, "RESOURCEFUL"},
        {FactionTraitSymbol::FLEXIBLE, "FLEXIBLE"},
        {FactionTraitSymbol::COOPERATIVE, "COOPERATIVE"},
        {FactionTraitSymbol::UNITED, "UNITED"},
        {FactionTraitSymbol::STRATEGIC, "STRATEGIC"},
        {FactionTraitSymbol::INTELLIGENT, "INTELLIGENT"},
        {FactionTraitSymbol::RESEARCH_FOCUSED, "RESEARCH_FOCUSED"},
        {FactionTraitSymbol::COLLABORATIVE, "COLLABORATIVE"},
        {FactionTraitSymbol::PROGRESSIVE, "PROGRESSIVE"},
        {FactionTraitSymbol::MILITARISTIC, "MILITARISTIC"},
        {FactionTraitSymbol::TECHNOLOGICALLY_ADVANCED,
         "TECHNOLOGICALLY_ADVANCED"},
        {FactionTraitSymbol::AGGRESSIVE, "AGGRESSIVE"},
        {FactionTraitSymbol::IMPERIALISTIC, "IMPERIALISTIC"},
        {FactionTraitSymbol::TREASURE_HUNTERS, "TREASURE_HUNTERS"},
        {FactionTraitSymbol::DEXTEROUS, "DEXTEROUS"},
        {FactionTraitSymbol::UNPREDICTABLE, "UNPREDICTABLE"},
        {FactionTraitSymbol::BRUTAL, "BRUTAL"},
        {FactionTraitSymbol::FLEETING, "FLEETING"},
        {FactionTraitSymbol::ADAPTABLE, "ADAPTABLE"},
        {FactionTraitSymbol::SELF_SUFFICIENT, "SELF_SUFFICIENT"},
        {FactionTraitSymbol::DEFENSIVE, "DEFENSIVE"},
        {FactionTraitSymbol::PROUD, "PROUD"},
        {FactionTraitSymbol::DIVERSE, "DIVERSE"},
        {FactionTraitSymbol::INDEPENDENT, "INDEPENDENT"},
        {FactionTraitSymbol::SELF_INTERESTED, "SELF_INTERESTED"},
        {FactionTraitSymbol::FRAGMENTED, "FRAGMENTED"},
        {FactionTraitSymbol::COMMERCIAL, "COMMERCIAL"},
        {FactionTraitSymbol::FREE_MARKETS, "FREE_MARKETS"},
        {FactionTraitSymbol::ENTREPRENEURIAL, "ENTREPRENEURIAL"},
    })

struct FactionTrait {
 public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(FactionTrait, symbol, name, description)

 public:
  FactionTraitSymbol symbol{};
  std::string name;
  std::string description;
};
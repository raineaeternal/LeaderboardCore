#include "LeaderboardCore.hpp"
#include "logging.hpp"

#include "scotland2/shared/modloader.h"
#include <vector>

namespace LeaderboardCore::API {
    void Registration::Register(const modloader::ModInfo &modInfo) {
        DEBUG("Registering leaderboard mod: {} with id: {}", modInfo.name, modInfo.id);
        _registeredLeaderboards.emplace(&modInfo);
    }

    void Registration::Unregister(const modloader::ModInfo &modInfo) {
        DEBUG("Unregistering leaderboard mod: {} with id: {}", modInfo->name, modInfo->id);
        _registeredLeaderboards.erase(&modInfo);
    }

    std::set<modloader::ModInfo *> Registration::GetLeaderboards() {
        return _registeredLeaderboards;
    }
}

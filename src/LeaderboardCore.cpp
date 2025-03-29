#include "LeaderboardCore.hpp"
#include "logging.hpp"

#include <vector>

namespace LeaderboardCore::API {
    void Registration::Register(const modloader::ModInfo &modInfo) {
        DEBUG("Registering leaderboard mod: {} with version: {}", modInfo.id, modInfo.version);
        _registeredLeaderboards.emplace(&modInfo);
    }

    void Registration::Unregister(const modloader::ModInfo &modInfo) {
        DEBUG("Unregistering leaderboard mod: {} with version: {}", modInfo.id, modInfo.version);
        _registeredLeaderboards.erase(&modInfo);
    }

    const std::set<const modloader::ModInfo *>& Registration::GetLeaderboards() {
        return _registeredLeaderboards;
    }
}

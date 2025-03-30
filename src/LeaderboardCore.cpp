#include "LeaderboardCore.hpp"
#include "logging.hpp"

#include <optional>

namespace LeaderboardCore::API {
    void Registration::Register(const modloader::ModInfo &modInfo, CustomLeaderboard *leaderboard) {
        DEBUG("Registering leaderboard mod: {} with version: {}", modInfo.id, modInfo.version);
        _registeredLeaderboards.emplace(&modInfo, leaderboard);
    }

    void Registration::Unregister(const modloader::ModInfo &modInfo) {
        DEBUG("Unregistering leaderboard mod: {} with version: {}", modInfo.id, modInfo.version);
        _registeredLeaderboards.erase(&modInfo);
    }

    const std::map<const modloader::ModInfo *, const CustomLeaderboard *>& Registration::GetLeaderboards() const {
        return _registeredLeaderboards;
    }

    std::optional<const CustomLeaderboard *> Registration::GetCustomLeaderboardFromModInfo(std::string_view modId) {
        for (const auto &[modInfo, regLeaderboard] : _registeredLeaderboards) {
            if (modInfo->id == modId) {
                return regLeaderboard;
            }
        }
        return std::nullopt;
    }
}

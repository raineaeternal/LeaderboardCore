#pragma once

#include "_config.hpp"
#include "scotland2/shared/loader.hpp"
#include <map>
#include <optional>

namespace LeaderboardCore::API {
    class Registration {
        public:
            static Registration get_instance();

            /// <summary>
            /// Register a leaderboard with LeaderboardCore.
            /// </summary>
            LBCORE_EXPORT void Register(const modloader::ModInfo& modInfo);

            LBCORE_EXPORT void Unregister(const modloader::ModInfo& modInfo);

            LBCORE_EXPORT const std::map<const modloader::ModInfo *, CustomLeaderboard *>& GetLeaderboards();

            LBCORE_EXPORT std::optional<const CustomLeaderboard *> GetCustomLeaderboardFromModInfo(std::string_view modId);

        private:
            std::map<const modloader::ModInfo *, CustomLeaderboard *> _registeredLeaderboards;
    };

}

#pragma once

#include "_config.hpp"
#include "scotland2/shared/modloader.h"
#include <set>

namespace LeaderboardCore::API {
    class Registration {
        public:
            /// <summary>
            /// Register a leaderboard with LeaderboardCore.
            /// </summary>
            LBCORE_EXPORT void Register(const modloader::ModInfo& modInfo);

            LBCORE_EXPORT void Unregister(const modloader::ModInfo& modInfo);

            LBCORE_EXPORT void GetLeaderboards();

            
        private:
            std::set<modloader::ModInfo *> _registeredLeaderboards;
    };

}

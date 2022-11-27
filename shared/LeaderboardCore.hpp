#pragma once
#include "Models/CustomLeaderboard.hpp"

namespace LeaderboardCore {
    namespace Register {
        /// @brief Register a custom leaderboard
        /// @param customLeaderboard the leaderboard to register
        /// @param modInfo the modInfo to register with, used for plugin ID. Does not have to be passed explicitly
        void RegisterLeaderboard(Models::CustomLeaderboard* leaderboard, const ModInfo& modInfo);

        /// @brief Unregisters a given custom leaderboard, make sure to clean up any new allocated pointers!
        /// @param customLeaderboard the leaderboard to unregister
        void UnregisterLeaderboard(Models::CustomLeaderboard* leaderboard);
    }
}
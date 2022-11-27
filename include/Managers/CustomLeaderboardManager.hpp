#pragma once

#include <unordered_map>
#include <unordered_set>
#include "Interfaces/INotifyLeaderboardChange.hpp"
#include "Models/CustomLeaderboard.hpp"

namespace LeaderboardCore::Managers {
    class CustomLeaderboardManager {
        public:
            /// @brief Register a custom leaderboard
            /// @param customLeaderboard the leaderboard to register
            /// @param modInfo the modInfo to register with, used for plugin ID. Does not have to be passed explicitly
            static void Register(Models::CustomLeaderboard* customLeaderboard, const ModInfo& modInfo = {MOD_ID, VERSION});

            /// @brief Unregisters a given custom leaderboard, make sure to clean up any new allocated pointers!
            /// @param customLeaderboard the leaderboard to unregister
            static void Unregister(Models::CustomLeaderboard* customLeaderboard);
        protected:
        private:
            static std::unordered_set<Interfaces::INotifyLeaderboardChange*> notifyCustomLeaderboardsChanges;
            static std::unordered_map<std::string, Models::CustomLeaderboard*> customLeaderboardsById;
            static void OnLeaderboardsChanged();
    };
}
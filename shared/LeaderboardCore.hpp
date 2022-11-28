#pragma once
#include "Models/CustomLeaderboard.hpp"
#include ""

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

    namespace Scoring {
        /// @brief Disable scoring with your mod Id for all leaderboards
        /// @param modInfo the modInfo of your mod
        /// @param reason the reason why you are disabling scores
        void Disable(const ModInfo& modInfo, const std::string_view& reason = "");

        /// @brief Disable scoring with your mod Id
        /// @param leaderboardId the id of the leaderboard you want to disable
        /// @param modInfo the modInfo of your mod
        /// @param reason the reason why you are disabling scores
        void Disable(const std::string& leaderboardId, const ModInfo& modInfo, const std::string_view& reason = "");

        /// @brief Enable scoring with your mod Id for all leaderboards
        /// @param modInfo the modInfo of your mod
        void Enable(const ModInfo& modInfo);

        /// @brief Enable scoring with your mod Id for all leaderboards
        /// @param leaderboardId the id of the leaderboard you want to enable
        /// @param modInfo the modInfo of your mod
        void Enable(const std::string& leaderboardId, const ModInfo& modInfo);

        /// @brief Get whether or not score submission is allowed for a specific leaderboard
        /// @param leaderboardId which leaderboard you are checking for, leave blank to check all of them
        bool GetScoreSubmissionAllowed(const std::string_view& leaderboardId = "");

        /// @brief  Gets the disabling mod infos & reasons for a specific leaderboard Id
        /// @param leaderboardId the id of the leaderboard you want to check
        /// @return map of mod infos and their disabling reasons
        const std::unordered_map<ModInfo, std::string>& GetDisablingModInfos(const std::string& leaderboardId);
        
        /// @brief Gets the ids of the currently registered leaderboards
        /// @return vectir of leaderboard ids;
        std::vector<std::string> GetLeaderboardIds();
    }
}
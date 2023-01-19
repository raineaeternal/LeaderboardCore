#pragma once

#include "modloader/shared/modloader.hpp"
#include <map>
namespace LeaderboardCore::Scoring {
    class ScoreDisabling {
        public:
            using DisableMap = std::unordered_map<std::string, std::string>;
            static void Disable(const ModInfo& modInfo, const std::string_view& reason);
            static void Disable(const std::string& leaderboardId, const ModInfo& modInfo, const std::string_view& reason);
            static void Enable(const ModInfo& modInfo);
            static void Enable(const std::string& leaderboardId, const ModInfo& modInfo);
            static bool GetScoreSubmissionAllowed(const std::string& leaderboardId);
            static void RegisterLeaderboard(const std::string& leaderboardId);
            static const DisableMap& GetDisablingModIds(const std::string& leaderboardId);
            static std::vector<std::string> GetLeaderboardIds();
        private:
            static std::unordered_map<std::string, DisableMap> disablingMods;
    };
}
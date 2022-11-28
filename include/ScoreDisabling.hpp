#pragma once

#include "modloader/shared/modloader.hpp"
#include <map>
namespace LeaderboardCore::Scoring {
    class ScoreDisabling {
        public:
            static void Disable(const ModInfo& modInfo, const std::string_view& reason);
            static void Disable(const std::string& leaderboardId, const ModInfo& modInfo, const std::string_view& reason);
            static void Enable(const ModInfo& modInfo);
            static void Enable(const std::string& leaderboardId, const ModInfo& modInfo);
            static bool GetScoreSubmissionAllowed(const std::string& leaderboardId);
            static void RegisterLeaderboard(const std::string& leaderboardId);
            static const std::unordered_map<ModInfo, std::string>& GetDisablingModInfos(const std::string& leaderboardId);
            static std::vector<std::string> GetLeaderboardIds();
        private:
            static std::unordered_map<std::string, std::unordered_map<ModInfo, std::string>> disablingMods;
    };
}
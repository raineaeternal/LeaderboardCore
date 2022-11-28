#include "LeaderboardCore.hpp"
#include "ScoreDisabling.hpp"
#include "Managers/CustomLeaderboardManager.hpp"

namespace LeaderboardCore {
    namespace Register {
        void RegisterLeaderboard(Models::CustomLeaderboard* leaderboard, const ModInfo& modInfo) {
            Managers::CustomLeaderboardManager::Register(leaderboard, modInfo);
        }

        void UnregisterLeaderboard(Models::CustomLeaderboard* leaderboard) {
            Managers::CustomLeaderboardManager::Unregister(leaderboard);
        }
    }

    namespace Scoring {
        void Disable(const ModInfo& modInfo, const std::string_view& reason) {
            ScoreDisabling::Disable(modInfo, reason);
        }

        void Disable(const std::string& leaderboardId, const ModInfo& modInfo, const std::string_view& reason) {
            ScoreDisabling::Disable(leaderboardId, modInfo, reason);
        }

        void Enable(const ModInfo& modInfo) {
            ScoreDisabling::Enable(modInfo);
        }

        void Enable(const std::string& leaderboardId, const ModInfo& modInfo) {
            ScoreDisabling::Enable(leaderboardId, modInfo);
        }

        bool GetScoreSubmissionAllowed(const std::string& leaderboardId) {
            return ScoreDisabling::GetScoreSubmissionAllowed(leaderboardId);
        }

        const std::unordered_map<ModInfo, std::string>& GetDisablingModInfos(const std::string& leaderboardId) {
            return ScoreDisabling::GetDisablingModInfos(leaderboardId);
        }

        std::vector<std::string> GetLeaderboardIds() {
            return ScoreDisabling::GetLeaderboardIds();
        }
    }
}
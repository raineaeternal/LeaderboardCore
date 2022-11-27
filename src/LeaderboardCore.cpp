#include "LeaderboardCore.hpp"
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
}
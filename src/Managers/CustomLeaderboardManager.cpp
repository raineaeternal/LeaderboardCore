#include "Managers/CustomLeaderboardManager.hpp"

namespace LeaderboardCore::Managers {
    std::unordered_set<Interfaces::INotifyLeaderboardChange*> CustomLeaderboardManager::notifyCustomLeaderboardsChanges;
    std::unordered_map<std::string, Models::CustomLeaderboard*> CustomLeaderboardManager::customLeaderboardsById;

    void CustomLeaderboardManager::Register(Models::CustomLeaderboard* customLeaderboard, const ModInfo& modInfo) {

    }

    void CustomLeaderboardManager::Unregister(Models::CustomLeaderboard* customLeaderboard) {
        
    }

    void CustomLeaderboardManager::OnLeaderboardsChanged() {
        
    }
}
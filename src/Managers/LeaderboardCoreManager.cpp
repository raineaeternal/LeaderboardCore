#include "Managers/LeaderboardCoreManager.hpp"

namespace LeaderboardCore::Managers {
    std::unordered_set<Interfaces::INotifyScoreSaberActivate *> LeaderboardCoreManager::notifyScoreSaberActivates;
    std::unordered_set<Interfaces::INotifyLeaderboardLoad *> LeaderboardCoreManager::notifyLeaderboardLoads;
    std::unordered_set<Interfaces::INotifyScoreUpload *> LeaderboardCoreManager::notifyScoreUploads;


    void LeaderboardCoreManager::LeaderboardActivated() {

    };

    void LeaderboardCoreManager::PanelViewLoadingChanged(bool loaded) {
        
    };

    void LeaderboardCoreManager::ScoreUploaded() {

    };
}

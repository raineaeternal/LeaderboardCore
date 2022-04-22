#include "include/Managers/LeaderboardCoreManager.hpp"

namespace LeaderboardCore {
    void LeaderboardCoreManager::PanelViewLoadingChanged(bool loaded) {
        for (auto& leaderboardLoads : m_notifyLeaderboardLoads) {
            leaderboardLoads->OnLeaderboardLoaded(loaded);
        }
    }

    void LeaderboardCoreManager::ScoreUploaded() {
        for (auto& scoreUploads : m_notifyScoreUploads) {
            scoreUploads->OnScoreUploaded();
        }
    }
}
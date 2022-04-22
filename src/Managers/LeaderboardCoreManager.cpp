#include "include/Managers/LeaderboardCoreManager.hpp"
using namespace LeaderboardCore;

namespace LeaderboardCore {
    LeaderboardCoreManager::m_notifyLeaderboardLoads;
    LeaderboardCoreManager::m_notifyScoreUploads;

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
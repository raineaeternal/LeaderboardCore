#pragma once

#include <vector>

#include "Interfaces/INotifyLeaderboardLoad.hpp"
#include "Interfaces/INotifyScoreUpload.hpp"

namespace LeaderboardCore {
    class LeaderboardCoreManager {
    private:
        std::vector<LeaderboardCore::Interfaces::INotifyLeaderboardLoad*> m_notifyLeaderboardLoads;
        std::vector<LeaderboardCore::Interfaces::INotifyScoreUpload*> m_notifyScoreUploads;

        void PanelViewLoadingChanged(bool loading);
        void ScoreUploaded();
    };
}
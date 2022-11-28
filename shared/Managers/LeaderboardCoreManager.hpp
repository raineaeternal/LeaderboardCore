#pragma once

#include <unordered_set>

#include "Interfaces/INotifyLeaderboardLoad.hpp"
#include "Interfaces/INotifyScoreSaberActivate.hpp"
#include "Interfaces/INotifyScoreUpload.hpp"

namespace LeaderboardCore::Managers {
    class LeaderboardCoreManager {
        // CHECKME: Since ScoreSaber will be integrating, is this truly necessary?
        /// @brief notifies if ScoreSaber activates
        void LeaderboardActivated();

        /// @brief Notifies leaderbords
        /// @param loaded 
        void PanelViewLoadingChanged(bool loaded);

        void ScoreUploaded();

    private:
        static std::unordered_set<Interfaces::INotifyScoreSaberActivate *> notifyScoreSaberActivates;
        static std::unordered_set<Interfaces::INotifyLeaderboardLoad *> notifyLeaderboardLoads;
        static std::unordered_set<Interfaces::INotifyScoreUpload *> notifyScoreUploads;
    };
}
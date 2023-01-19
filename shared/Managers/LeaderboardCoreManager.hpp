#pragma once

#include <unordered_set>

#include "Interfaces/INotifyLeaderboardLoad.hpp"
#include "Interfaces/INotifyScoreSaberActivate.hpp"
#include "Interfaces/INotifyScoreUpload.hpp"

namespace LeaderboardCore::Managers {
    class LeaderboardCoreManager {
        // CHECKME: Since ScoreSaber will be integrating, is this truly necessary?
        /// @brief notifies if ScoreSaber activates
        static void LeaderboardActivated();

        /// @brief Notifies leaderboards
        /// @param loaded whether it was just loaded or unloaded
        static void PanelViewLoadingChanged(bool loaded);

        /// @brief notifies if a score was uploaded
        static void ScoreUploaded();

    private:
        static std::unordered_set<Interfaces::INotifyScoreSaberActivate *> notifyScoreSaberActivates;
        static std::unordered_set<Interfaces::INotifyLeaderboardLoad *> notifyLeaderboardLoads;
        static std::unordered_set<Interfaces::INotifyScoreUpload *> notifyScoreUploads;
    };
}
#pragma once

#include "_config.hpp"
namespace LeaderboardCore::API {
    namespace Registration {
        /// <summary>
        /// Register a leaderboard with LeaderboardCore.
        /// </summary>
        LBCORE_EXPORT_FUNC void RegisterLeaderboard(std::string modId = MOD_ID);

        /// <summary>
        /// Unregister a leaderboard with LeaderboardCore.
        /// </summary>
        LBCORE_EXPORT_FUNC void UnregisterLeaderboard(std::string modId = MOD_ID);
    }
    namespace Leaderboard {
        /// <summary>
        /// Notify subcribers that the leaderboard has been set.
        /// </summary>
        LBCORE_EXPORT_FUNC void NotifyLeaderboardSet();
    }

}

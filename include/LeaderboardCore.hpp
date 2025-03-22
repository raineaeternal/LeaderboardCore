#pragma once

namespace LeaderboardCore::API {
    namespace Registration {
        /// <summary>
        /// Register a leaderboard with LeaderboardCore.
        /// </summary>
        void RegisterLeaderboard(MOD_ID const& modID);

        /// <summary>
        /// Unregister a leaderboard with LeaderboardCore.
        /// </summary>
        void UnregisterLeaderboard(MOD_ID const& modID);
    }
    namespace Leaderboard {
        /// <summary>
        /// Notify subcribers that the leaderboard has been set.
        /// </summary>
        void NotifyLeaderboardSet();
    }
}

#include "LeaderboardCore.hpp"
#include "logging.hpp"

namespace LeaderboardCore::API {
    namespace Registration {
        /// <summary>
        /// Register a leaderboard with LeaderboardCore.
        /// </summary>
        void RegisterLeaderboard(MOD_ID const& modID) {
            DEBUG("Registering leaderboard with MOD_ID: {}", modID);
        }

        /// <summary>
        /// Unregister a leaderboard with LeaderboardCore.
        /// </summary>
        void UnregisterLeaderboard(MOD_ID const& modID) {
            DEBUG("Unregistering leaderboard with MOD_ID: {}", modID);
        }
    }
    namespace Leaderboard {
        /// <summary>
        /// Notify subcribers that the leaderboard has been set.
        /// </summary>
        void NotifyLeaderboardSet() {
            DEBUG("Notifying subscribers that the leaderboard has been set.");
        }
    }

}

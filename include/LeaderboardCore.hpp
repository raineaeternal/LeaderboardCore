#pragma once

namespace LeaderboardCore::API {
    namespace Registration {
        void RegisterLeaderboard(MOD_ID const& modID);

        void UnregisterLeaderboard(MOD_ID const& modID);
    }

    namespace Leaderboard {
        void NotifyLeaderboardSet();
    }
}

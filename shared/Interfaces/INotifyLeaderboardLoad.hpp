#pragma once

namespace LeaderboardCore::Interfaces {
    class INotifyLeaderboardLoad {
        void OnLeaderboardLoaded(bool loaded);
    };
}
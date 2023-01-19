#pragma once

namespace LeaderboardCore::Interfaces {
    class INotifyLeaderboardLoad {
    public:
        virtual void OnLeaderboardLoaded() = 0;
    };
}
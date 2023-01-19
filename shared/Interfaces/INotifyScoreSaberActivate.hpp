#pragma once

namespace LeaderboardCore::Interfaces {
    class INotifyScoreSaberActivate {
    public:
        virtual void OnScoreSaberActivated() = 0;
    };
}
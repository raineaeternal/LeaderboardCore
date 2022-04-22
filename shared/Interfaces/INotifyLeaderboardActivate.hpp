#pragma once

namespace LeaderboardCore::Interfaces {
    class INotifyScoreSaberActive {
    public:
        virtual void OnScoreSaberActivated() = 0;
    };
}

#pragma once

namespace LeaderboardCore::Interfaces {
    class INotifyScoreUpload {
    public:
        virtual void OnScoreUpload() = 0;
    };
}
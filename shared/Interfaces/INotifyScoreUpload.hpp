#pragma once

namespace LeaderboardCore::Interfaces {
    class INotifyScoreUpload {
    public:
        virtual void OnScoreUploaded() = 0;
    };
}
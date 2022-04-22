#pragma once

namespace LeaderboardCore::Interfaces {
    class INotifyScoreUpload {
    public:
        void OnScoreUploaded();
    };
}
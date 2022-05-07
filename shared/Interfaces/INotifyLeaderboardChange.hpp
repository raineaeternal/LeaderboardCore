#pragma once

#include <map>
#include "shared/Models/CustomLeaderboard.hpp"

namespace LeaderboardCore::Interfaces {
    class INotifyLeaderboardChange {
    public:
        virtual void OnLeaderboardChange(const std::vector<LeaderboardCore::Models::CustomLeaderboard*> customLeaderboards);
    };
}
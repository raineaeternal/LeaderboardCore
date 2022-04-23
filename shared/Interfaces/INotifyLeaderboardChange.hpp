#pragma once

#include <map>
#include "shared/Models/CustomLeaderboard.hpp"

namespace LeaderboardCore::Interfaces {
    class INotifyLeaderboardChange {
    public:
        virtual void OnLeaderboardChange(std::vector<LeaderboardCore::Models::CustomLeaderboard*> customLeaderboards);
    };
}
#pragma once

#include <map>
#include "shared/CustomLeaderboard.hpp"

namespace LeaderboardCore::Interfaces {
    class INotifyLeaderboardChange {
    public:
        virtual void OnLeaderboardChange(std::map<CustomLeaderboard> customLeaderboards) = 0;
    };
}
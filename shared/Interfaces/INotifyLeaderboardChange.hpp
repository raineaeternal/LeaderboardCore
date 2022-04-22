#pragma once

#include <map>
#include "shared/CustomLeaderboard.hpp"

namespace LeaderboardCore::Interfaces {
    class INotifyLeaderboardSet{
    public:
        void OnLeaderboardChange(std::map<CustomLeaderboard> customLeaderboards);
    };
}
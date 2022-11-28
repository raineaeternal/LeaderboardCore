#pragma once

#include <set>
#include "Models/CustomLeaderboard.hpp"

namespace LeaderboardCore::Interfaces {
    class INotifyLeaderboardChange {
    public:
        virtual void OnLeaderboardsChanged(const std::set<Models::CustomLeaderboard*>& orderedCustomLeaderboards, const std::unordered_map<std::string, Models::CustomLeaderboard*>& customLeaderboardsById) = 0;
    };
}
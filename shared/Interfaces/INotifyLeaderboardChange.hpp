#pragma once

namespace LeaderboardCore::Interfaces {
    class INotifyLeaderboardChange {
        virtual void OnLeaderboardsChanged(const std::set<Models::CustomLeaderboard*>& orderedCustomLeaderboards, const std::unordered_map<std::string, Models::CustomLeaderboard*>& customLeaderboardsById) = 0;
    };
}
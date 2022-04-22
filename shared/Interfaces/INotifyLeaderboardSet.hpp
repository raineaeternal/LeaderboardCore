#pragma once

#include "GlobalNamespace/IDifficultyBeatmap.hpp"

namespace LeaderboardCore::Interfaces {
    class INotifyLeaderboardSet{
    public:
        virtual void OnLeaderboardSet(IDifficultyBeatmap* diff) = 0;
    };
}
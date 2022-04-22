#pragma once

#include "GlobalNamespace/IDifficultyBeatmap.hpp"

namespace LeaderboardCore::Interfaces {
    class INotifyLeaderboardSet{
    public:
        void OnLeaderboardSet(IDifficultyBeatmap* diff);
    };
}
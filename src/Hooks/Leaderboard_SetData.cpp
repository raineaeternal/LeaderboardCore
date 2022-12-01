#include "hooking.h"
#include "LeaderboardCore.hpp"
#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"

// REPLACES ORIG
MAKE_AUTO_HOOK_ORIG_MATCH(Leaderboard_SetData, &GlobalNamespace::PlatformLeaderboardViewController::SetData, void, GlobalNamespace::PlatformLeaderboardViewController* self, GlobalNamespace::IDifficultyBeatmap* difficultyBeatmap) {
    //Leaderboard_SetData(self, difficultyBeatmap);
    LeaderboardCore::Events::NotifyLeaderboardSet().invoke(difficultyBeatmap);
}
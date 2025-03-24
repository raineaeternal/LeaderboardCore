#pragma once

#include "GlobalNamespace/BeatmapKey.hpp"
#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "hooking.hpp"

MAKE_AUTO_HOOK_MATCH(
    Leaderboard_SetData,
    &GlobalNamespace::PlatformLeaderboardViewController::SetData, void,
    GlobalNamespace::PlatformLeaderboardViewController *self,
    ByRef<GlobalNamespace::BeatmapKey> beatmapKey) {
  Leaderboard_SetData(self, beatmapKey);
}

#include "hooking.h"

#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"

MAKE_AUTO_HOOK_MATCH(Leaderboard_Refresh, &GlobalNamespace::PlatformLeaderboardViewController::Refresh, void, GlobalNamespace::PlatformLeaderboardViewController* self, bool showLoadingIndicator, bool clear) {
    Leaderboard_Refresh(self, showLoadingIndicator, clear);
}
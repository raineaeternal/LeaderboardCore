#include "hooking.h"

#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"

MAKE_AUTO_HOOK_MATCH(Leaderboard_DidActivate, &GlobalNamespace::PlatformLeaderboardViewController::DidActivate, void, GlobalNamespace::PlatformLeaderboardViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    Leaderboard_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

MAKE_AUTO_HOOK_MATCH(Leaderboard_DidDeactivate, &GlobalNamespace::PlatformLeaderboardViewController::DidDeactivate, void, GlobalNamespace::PlatformLeaderboardViewController* self, bool removedFromHierarchy, bool screenSystemDisabling) {
    Leaderboard_DidDeactivate(self, removedFromHierarchy, screenSystemDisabling);
}
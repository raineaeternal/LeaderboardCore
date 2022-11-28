#include "hooking.h"

#include "Hooks/Leaderboard_DidActivate_DidDeactivate.hpp"

MAKE_AUTO_HOOK_MATCH(Leaderboard_DidActivatePre, &GlobalNamespace::PlatformLeaderboardViewController::DidActivate, void, GlobalNamespace::PlatformLeaderboardViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    LeaderboardCore::Hooks::LeaderboardPrefixFields::platformLeaderboardViewController = self;
    
    Leaderboard_DidActivatePre(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

MAKE_AUTO_HOOK_MATCH(Leaderboard_DidActivatePost, &GlobalNamespace::PlatformLeaderboardViewController::DidActivate, void, GlobalNamespace::PlatformLeaderboardViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    Leaderboard_DidActivatePost(self, firstActivation, addedToHierarchy, screenSystemEnabling);


}

MAKE_AUTO_HOOK_MATCH(Leaderboard_DidDeactivate, &GlobalNamespace::PlatformLeaderboardViewController::DidDeactivate, void, GlobalNamespace::PlatformLeaderboardViewController* self, bool removedFromHierarchy, bool screenSystemDisabling) {
    Leaderboard_DidDeactivate(self, removedFromHierarchy, screenSystemDisabling);
}
#include "hooking.h"
#include "logger.h"

#include "Hooks/Leaderboard_DidActivate_DidDeactivate.hpp"

GlobalNamespace::PlatformLeaderboardViewController* LeaderboardCore::Hooks::LeaderboardPrefixFields::platformLeaderboardViewController = nullptr;
UnorderedEventCallback<bool, bool, bool> LeaderboardCore::Hooks::PlatformLeaderboardViewControllerEvents::didActivateEvent = {};

MAKE_AUTO_HOOK_MATCH(PlatformLeaderboardViewController_DidActivate, &GlobalNamespace::PlatformLeaderboardViewController::DidActivate, void, GlobalNamespace::PlatformLeaderboardViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    LeaderboardCore::Hooks::LeaderboardPrefixFields::platformLeaderboardViewController = self;
    DEBUG("PlatformLeaderboardViewController activate!");
    PlatformLeaderboardViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    if (LeaderboardCore::Hooks::PlatformLeaderboardViewControllerEvents::didActivateEvent.size() > 0) 
        LeaderboardCore::Hooks::PlatformLeaderboardViewControllerEvents::didActivateEvent.invoke(firstActivation, addedToHierarchy, screenSystemEnabling);
}

MAKE_AUTO_HOOK_MATCH(Leaderboard_DidDeactivate, &GlobalNamespace::PlatformLeaderboardViewController::DidDeactivate, void, GlobalNamespace::PlatformLeaderboardViewController* self, bool removedFromHierarchy, bool screenSystemDisabling) {
    Leaderboard_DidDeactivate(self, removedFromHierarchy, screenSystemDisabling);
}